// Bej3Hax.Injector.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <Windows.h>

#include <TlHelp32.h>
#include <easyhook.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <filesystem>
#include <Settings.h>

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
    } while (Process32Next(hndl, &process));

    CloseHandle(hndl);
  }
  return 0;
}

int main() {
  std::filesystem::path dllPath = std::filesystem::current_path().parent_path() / "Debug" / "Bej3Hax.dll";
  wprintf(L"Attempting to inject: %s\n\n", dllPath.wstring().c_str());

  auto processId = FindProcessID(L"Bejeweled3.exe");

  if (processId == 0) {
    std::cerr << "Could not find Bejeweled 3 process. Please make sure "
                 "Bejeweled 3 is running";
    return 1;
  }

  Settings settings;
  settings.swapAlwaysSucceeds = true;
  settings.pieceFlags = Sexy::Piece::PieceFlags::Supernova;

  // Inject dllToInject into the target process Id, passing
  // freqOffset as the pass through data.
  NTSTATUS nt =
      RhInjectLibrary(processId,  // The process to inject into
                      0,          // ThreadId to wake up upon injection
                      EASYHOOK_INJECT_DEFAULT,
                      dllPath.wstring().data(),  // 32-bit
                      nullptr,          // 64-bit not provided
                      &settings,  // data to send to injected DLL entry point
                      sizeof(settings)         // size of data to send
      );

  if (nt != 0) {
    printf("RhInjectLibrary failed with error code = %d\n", nt);
    PWCHAR err = RtlGetLastErrorString();
    std::wcout << err << "\n";
  } else {
    std::wcout << L"Library injected successfully.\n";
  }

  std::wcout << "Press Enter to exit";
  std::wstring input;
  std::getline(std::wcin, input);
  std::getline(std::wcin, input);
  return 0;
}

#pragma comment(lib, "Psapi.lib")
#if _WIN64
#pragma comment(lib, "EasyHook64.lib")
#else
#pragma comment(lib, "EasyHook32.lib")
#endif
