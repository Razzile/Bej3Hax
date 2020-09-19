#include "pch.h"

#include <Windows.h>
#include <easyhook.h>

#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Hooks.h"

// EasyHook will be looking for this export to support DLL injection. If not
// found then DLL injection will fail.
extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(
    REMOTE_ENTRY_INFO* inRemoteInfo);

void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo) {
  spdlog::set_level(spdlog::level::info);
#ifdef _DEBUG
  spdlog::set_level(spdlog::level::debug);

  // Allocate a new console window and reopen standard IO streams
  AllocConsole();

  freopen("CONIN$", "r", stdin);
  freopen("CONOUT$", "w", stdout);
  freopen("CONOUT$", "w", stderr);
#endif

  auto logger = spdlog::stdout_color_mt("Bej3hax");
  spdlog::set_default_logger(logger);

  spdlog::debug("Injected by process Id: {}" , inRemoteInfo->HostPID);
  spdlog::debug("Received {} bytes from injector", inRemoteInfo->UserDataSize);


  // copy settings from injector
  Hooks::settings = *reinterpret_cast<Settings*>(inRemoteInfo->UserData);

  spdlog::debug("Loaded settings: {}", Hooks::settings);

  spdlog::info("Initializing hooks");

  Hooks::InitializeHooks();
}

#if _WIN64
#pragma comment(lib, "EasyHook64.lib")
#else
#pragma comment(lib, "EasyHook32.lib")
#endif