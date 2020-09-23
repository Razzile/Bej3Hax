#include "pch.h"

#include "DirectX.h"

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>


typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
WNDPROC oWndProc;

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg,
                                              WPARAM wParam, LPARAM lParam);

Hook<D3D9_Present> d3d9_Present_hook_(0x0);
std::string window_name_;

static bool menu_open_ = false;

bool DirectXHook::Initialize(std::string window_name) {
  auto module = GetModuleHandleA("Bejeweled3.exe");
  window_name_ = window_name;
  auto temp_window = CreateWindowA(
      "BUTTON", "Temp Window", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,
      CW_USEDEFAULT, 300, 300, NULL, NULL, module, NULL);

  if (!temp_window) {
    spdlog::error("Failed to acquire window handle");
    return false;
  }

  IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

  if (!pD3D) {
    spdlog::error("Failed to create D3D9 instance");
    pD3D->Release();
    DestroyWindow(temp_window);
    return false;
  }

  D3DPRESENT_PARAMETERS d3dpp{0};
  d3dpp.hDeviceWindow = temp_window;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.Windowed = TRUE;
  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

  IDirect3DDevice9* device = nullptr;
  auto result = pD3D->CreateDevice(
      D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
      D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT,
      &d3dpp, &device);
  if (FAILED(result)) {
    const char* err_type = "<unknown>";
    if (result == D3DERR_DEVICELOST) {
      err_type = "D3DERR_DEVICELOST";
    } else if (result == D3DERR_INVALIDCALL) {
      err_type = "D3DERR_INVALIDCALL";
    } else if (result == D3DERR_NOTAVAILABLE) {
      err_type = "D3DERR_NOTAVAILABLE";
    } else if (result == D3DERR_OUTOFVIDEOMEMORY) {
      err_type = "D3DERR_OUTOFVIDEOMEMORY";
    }
    spdlog::error("Failed to create d3d9 device [error code: {0} - {1}]",
                  result, err_type);
    pD3D->Release();
    DestroyWindow(temp_window);
    return false;
  }

  void** pVTable = *reinterpret_cast<void***>(device);

  if (device) {
    device->Release();
    pD3D->Release();
    DestroyWindow(temp_window);
  }

  spdlog::info("Installing WndProc hook");
  auto window = FindWindowA(nullptr, window_name_.c_str());
  oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWL_WNDPROC,
                                                        reinterpret_cast<
                                                          LONG_PTR>(WndProc)));

  spdlog::info("Installing D3D9 hook");

  auto present_hook =
      Hook<D3D9_Present>(reinterpret_cast<uintptr_t>(pVTable[17]));
  d3d9_Present_hook_ = std::move(present_hook);
  // d3d9_EndScene_hook_.Initialize(MyEndScene);
  d3d9_Present_hook_.Initialize(MyPresent);
  return true;
}

HRESULT __stdcall DirectXHook::MyPresent(IDirect3DDevice9* device,
                                         const RECT* pSourceRect,
                                         const RECT* pDestRect,
                                         HWND hDestWindowOverride,
                                         const RGNDATA* pDirtyRegion) {
  static bool initialized = false;
  if (!initialized) {
    spdlog::debug("Initializing imgui");

    initialized = true;
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.WantCaptureMouse = true;

    ImGui_ImplWin32_Init(FindWindowA(NULL, window_name_.c_str()));
    ImGui_ImplDX9_Init(device);
  }

  if (menu_open_) {
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
  }

  return d3d9_Present_hook_.original(device, pSourceRect, pDestRect,
                                     hDestWindowOverride, pDirtyRegion);
}

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_KEYUP: {
      if (wParam == VK_F3) {
        menu_open_ = !menu_open_;
      }
      break;
    }
    case WM_MBUTTONDOWN: {
      if (menu_open_) {
        return true;
      }
      break;
    }
    default:
      break;
  }

  if (menu_open_) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
  }

  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
