#pragma once

#include <ostream>

#include "Bejeweled.h"

struct Settings {
  int pieceFlags;
  bool swapAlwaysSucceeds;

  friend std::ostream& operator<<(std::ostream&, const Settings& settings);
};

inline std::ostream& operator<<(std::ostream& out, const Settings& settings) {
  out << "\n\tpieceFlags: " << std::hex << settings.pieceFlags << "\n\t"
      << "swapAlwaysSucceeds: " << std::boolalpha << settings.swapAlwaysSucceeds
      << std::endl;
  return out;
}