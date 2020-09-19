#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

struct Settings {
  int pieceFlags;
  bool swapAlwaysSucceeds;

  template <typename OStream>
  friend OStream& operator<<(OStream&, const Settings& settings);
};

template <typename OStream>
OStream& operator<<(OStream& out, const Settings& settings) {
  out << "[pieceFlags=" << std::hex << settings.pieceFlags << ", "
      << "swapAlwaysSucceeds=" << std::boolalpha << settings.swapAlwaysSucceeds
      << "]";
  return out;
}