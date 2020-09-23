#pragma once

#include <Bejeweled.h>
#include "Hook.h"
#include "Settings.h"

namespace Hooks {

extern Settings settings;

using namespace Sexy;

extern Board::GetSelectedPiece oGetSelectedPiece;

void _fastcall MyDoUpdate(Board* self, void* skip);

bool _fastcall MyTrySwap(Board* self, void* skip, Piece* piece,
                         int x, int y, bool always_allow, bool unk1, bool unk2);

void InitializeHooks();

}  // namespace Hooks