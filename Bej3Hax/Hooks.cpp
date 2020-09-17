#include "pch.h"

#include "Hooks.h"

using namespace Sexy;

Settings Hooks::settings;

Board::GetSelectedPiece Hooks::oGetSelectedPiece = nullptr;
Board::TrySwap Hooks::oTrySwap = nullptr;
Board::UpdateGame Hooks::oUpdateGame = nullptr;
Board::DoUpdate Hooks::oDoUpdate = nullptr;

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
  oDoUpdate(self);
  Sexy::Piece* piece = GetSelectedPieceHelper(self);
  if (piece) {
    piece->flags = Piece::Bomb;
  }
}

bool _fastcall Hooks::MyTrySwap(Board* self, void* skip, Piece* piece, int x,
                                int y, bool always_allow, bool unk1,
                                bool unk2) {
  if (settings.pieceFlags >= 0) {
    piece->flags = static_cast<Sexy::Piece::PieceFlags>(settings.pieceFlags);
  }
  always_allow = (settings.swapAlwaysSucceeds) ? true : always_allow;
  return oTrySwap(self, piece, x, y, always_allow, unk1, unk2);
}