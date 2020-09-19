#include "pch.h"

#include "Hooks.h"

#include "Hook.h"

using namespace Sexy;

constexpr uintptr_t kTrySwapAddr = 0x75EE20;
constexpr uintptr_t kGetSelectedPieceAddr = 0x73BF00;
constexpr uintptr_t kUpdateGameAddr = 0x767E20;
constexpr uintptr_t kDoUpdateAddr = 0x767090;

Settings Hooks::settings;

Board::GetSelectedPiece Hooks::oGetSelectedPiece = nullptr;

Hook<kDoUpdateAddr, Board::DoUpdate> doUpdateHook;
Hook<kTrySwapAddr, Board::TrySwap> trySwapHook;

__declspec(naked) Sexy::Piece* _fastcall GetSelectedPieceHelper(
    Sexy::Board* board) {
  __asm {
    mov esi, ecx
    mov edx, Hooks::oGetSelectedPiece
    call edx
    ret
  }
}

void __fastcall Hooks::MyDoUpdate(Board* self, void* skip) {
  doUpdateHook.original(self);

  Piece* piece = GetSelectedPieceHelper(self);
  if (piece && settings.pieceFlags >= 0) {
    piece->flags = static_cast<Sexy::Piece::PieceFlags>(settings.pieceFlags);
  }
}

bool _fastcall Hooks::MyTrySwap(Board* self, void* skip, Piece* piece, int x,
                                int y, bool always_allow, bool unk1,
                                bool unk2) {
  always_allow = (settings.swapAlwaysSucceeds) ? true : always_allow;
  return trySwapHook.original(self, piece, x, y, always_allow, unk1, unk2);
}

void Hooks::InitializeHooks() {
  oGetSelectedPiece = decltype(oGetSelectedPiece)(0x73BF00);

  doUpdateHook.Initialize(MyDoUpdate);
  trySwapHook.Initialize(MyTrySwap);
}
