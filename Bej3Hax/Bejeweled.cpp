#include "pch.h"
#include "Bejeweled.h"

Sexy::Board::TrySwap Hooks::oTrySwap = nullptr;

bool _fastcall Hooks::MyTrySwap(Sexy::Board* self, void* skip, Sexy::Piece* piece, int x,
                              int y,
                               bool always_allow, bool unk1, bool unk2) {
  return oTrySwap(self, piece, x, y, true, unk1, unk2);
}