#pragma once

namespace Sexy {

struct Piece {
  enum PieceFlags {
    Normal = 0 << 0,
    Bomb = 1 << 0,
    Hypercube = 1 << 1,
    Electric = 1 << 2,
    Unk1 = 1 << 3,       // Unsure what this does
    BigPoints = 1 << 5,  // ??? not sure what exactly this is
    TimeBomb = 1 << 6,
    Butterfly = 1 << 7,
    LockedGem = 1 << 8,  // This gem type doesn't appear to be in any game mode,
    Unk2 = 1 << 9,  // Seems to show the bomb effect when it has ticked to 0,
                    // perhaps another member var in Sexy::Piece contains the
                    // "clock" for the bomb
    DigPoints = 1 << 10,   // Triggers the sound effect from diamond mine
    LastHurrah = 1 << 19,  // Triggers the Last Hurrah explosions,
    MysteryGem = 1 << 13,
    Supernova = Bomb | Electric,
  };

  char unk[0x228];
  PieceFlags flags;
};

struct Board {
  typedef bool(__thiscall* TrySwap)(Sexy::Board* _this, Sexy::Piece* piece,
                                    int x, int y, bool always_allow, bool unk1,
                                    bool unk2);
};

}  // namespace Sexy