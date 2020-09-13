#include "pch.h"
#include "Hooks.h"

Settings Hooks::settings;

Sexy::Board::TrySwap Hooks::oTrySwap = nullptr;

bool _fastcall Hooks::MyTrySwap(Sexy::Board* self, void* skip, Sexy::Piece* piece, int x,
                              int y,
                               bool always_allow, bool unk1, bool unk2) {
  if (settings.pieceFlags >= 0) {
    piece->flags = static_cast<Sexy::Piece::PieceFlags>(settings.pieceFlags);
  }
  always_allow = (settings.swapAlwaysSucceeds) ? true : always_allow;
  return oTrySwap(self, piece, x, y, always_allow, unk1, unk2);
}