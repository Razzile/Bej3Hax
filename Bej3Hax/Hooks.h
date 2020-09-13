#pragma once

#include <Bejeweled.h>

#include "Settings.h"

namespace Hooks {

extern Settings settings;

extern Sexy::Board::TrySwap oTrySwap;
bool _fastcall MyTrySwap(Sexy::Board* self, void* skip, Sexy::Piece* piece,
                         int x, int y, bool always_allow, bool unk1, bool unk2);

}  // namespace Hooks