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
  HOOK_TRACE_INFO hHook = {NULL};  // keep track of our hook

  auto baseAddress = GetModuleHandle(L"Bejeweled3.exe");

  auto trySwapAddr = 0x75EE20;  // - (DWORD)baseAddress;

  // copy settings from injector
  Hooks::settings = *reinterpret_cast<Settings*>(inRemoteInfo->UserData);

  std::cout << "Loaded settings: " << Hooks::settings;

  Hooks::oTrySwap = decltype(Hooks::oTrySwap)(trySwapAddr);

  // Install the hook
  NTSTATUS result = LhInstallHook((void*)trySwapAddr, Hooks::MyTrySwap,
                                  nullptr, &hHook);
  if (FAILED(result)) {
    std::wstring s(RtlGetLastErrorString());
    std::wcout << "Failed to install hook: " << std::endl;
    std::wcout << s;
  } else {
    std::cout << "Hooks installed successfully." << std::endl;
  }

  std::cout << "TrySwap callback: " << static_cast<void*>(&Hooks::oTrySwap) << std::endl;

  // If the threadId in the ACL is set to 0,
  // then internally EasyHook uses GetCurrentThreadId()
  ULONG ACLEntries[1] = {0};

  // Disable the hook for the provided threadIds, enable for all others
  LhSetExclusiveACL(ACLEntries, 1, &hHook);

  return;
}

#if _WIN64
#pragma comment(lib, "EasyHook64.lib")
#else
#pragma comment(lib, "EasyHook32.lib")
#endif