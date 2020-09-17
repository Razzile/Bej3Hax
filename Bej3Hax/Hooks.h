#pragma once

#include <Bejeweled.h>

#include "Settings.h"

namespace Hooks {

extern Settings settings;

using namespace Sexy;

extern Board::GetSelectedPiece oGetSelectedPiece;
extern Board::UpdateGame oUpdateGame;

extern Board::DoUpdate oDoUpdate;
void _fastcall MyDoUpdate(Board* self, void* skip);

extern Board::TrySwap oTrySwap;
bool _fastcall MyTrySwap(Board* self, void* skip, Piece* piece,
                         int x, int y, bool always_allow, bool unk1, bool unk2);

}  // namespace Hooks