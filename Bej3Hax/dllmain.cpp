#include "pch.h"

#include <Windows.h>
#include <easyhook.h>

#include <iostream>
#include <string>

#include "Hooks.h"

// EasyHook will be looking for this export to support DLL injection. If not
// found then DLL injection will fail.
extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(
    REMOTE_ENTRY_INFO* inRemoteInfo);

void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo) {
#ifdef _DEBUG
  AllocConsole();

  freopen("CONIN$", "r", stdin);
  freopen("CONOUT$", "w", stdout);
  freopen("CONOUT$", "w", stderr);
#endif

  std::cout << "Injected by process Id: " << inRemoteInfo->HostPID << "\n";
  std::cout << "Passed in data size: " << inRemoteInfo->UserDataSize << "\n";

  // Perform hooking
  HOOK_TRACE_INFO trySwapHook = {nullptr};
  HOOK_TRACE_INFO doUpdateHook = {nullptr};

  auto baseAddress = GetModuleHandle(L"Bejeweled3.exe");



  // copy settings from injector
  Hooks::settings = *reinterpret_cast<Settings*>(inRemoteInfo->UserData);

  std::cout << "Loaded settings: " << Hooks::settings;

  std::cout << "Initializing hooks" << std::endl;

  Hooks::InitializeHooks();
}

#if _WIN64
#pragma comment(lib, "EasyHook64.lib")
#else
#pragma comment(lib, "EasyHook32.lib")
#endif