// Bej3Hax.Injector.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <Windows.h>

#include <Bejeweled.h>
#include <Settings.h>
#include <TlHelp32.h>
#include <easyhook.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <string>

DWORD FindProcessID(std::wstring procName) {
  HANDLE hndl =
      CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0);
  if (hndl) {
    PROCESSENTRY32 process = {sizeof(PROCESSENTRY32)};
    Process32First(hndl, &process);
    do {
      if (procName == process.szExeFile) {
        CloseHandle(hndl);
        return process.th32ProcessID;
      }
    }
    while (Process32Next(hndl, &process));

    CloseHandle(hndl);
  }
  return 0;
}

int main() {
#ifdef _DEBUG
  spdlog::set_level(spdlog::level::debug);

  std::filesystem::path dllPath =
      std::filesystem::current_path().parent_path() / "Debug" / "Bej3Hax.dll";
#else
  spdlog::set_level(spdlog::level::info);
  std::filesystem::path dllPath =
      std::filesystem::current_path().parent_path() / "Release" / "Bej3Hax.dll";
#endif

  spdlog::info("Attempting to inject: {}", dllPath.string());

  auto processId = FindProcessID(L"Bejeweled3.exe");

  if (processId == 0) {
    spdlog::error(
        "Could not find Bejeweled 3 process. Please make sure "
        "Bejeweled 3 is running");
    return 1;
  }

  Settings settings;
  settings.swapAlwaysSucceeds = true;
  settings.pieceFlags = static_cast<int>(Sexy::Piece::PieceFlags::Supernova);

  // Inject dllToInject into the target process Id, passing
  // freqOffset as the pass through data.
  NTSTATUS nt =
      RhInjectLibrary(processId, // The process to inject into
                      0,         // ThreadId to wake up upon injection
                      EASYHOOK_INJECT_DEFAULT,
                      dllPath.wstring().data(), // 32-bit
                      nullptr,                  // 64-bit not provided
                      &settings,
                      // data to send to injected DLL entry point
                      sizeof(settings) // size of data to send
          );

  if (nt != 0) {
    PWCHAR err = RtlGetLastErrorString();
    spdlog::error("RhInjectLibrary failed with error {0} [code = {1}]", nt,
                  fmt::to_string(err));
  } else {
    spdlog::info("Library injected successfully.\n");
  }
  return 0;
}

#pragma comment(lib, "Psapi.lib")
#if _WIN64
#pragma comment(lib, "EasyHook64.lib")
#else
#pragma comment(lib, "EasyHook32.lib")
#endif
