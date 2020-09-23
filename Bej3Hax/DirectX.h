#pragma once
#include <d3d9.h>

#include <memory>

#include "Hook.h"

typedef LRESULT(__stdcall* D3D9_EndScene)(IDirect3DDevice9*);
typedef LRESULT(__stdcall* D3D9_Present)(IDirect3DDevice9*,
                                         const RECT* pSourceRect,
                                         const RECT* pDestRect,
                                         HWND hDestWindowOverride,
                                         const RGNDATA* pDirtyRegion);

namespace DirectXHook {
bool Initialize(std::string window_name = "Bejeweled 3");

static HRESULT __stdcall MyPresent(IDirect3DDevice9* device,
                                   const RECT* pSourceRect,
                                   const RECT* pDestRect,
                                   HWND hDestWindowOverride,
                                   const RGNDATA* pDirtyRegion);
};  // namespace DirectXHook
