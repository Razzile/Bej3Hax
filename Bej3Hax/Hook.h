#pragma once
#include <easyhook.h>

#include <functional>
#include <type_traits>

#include <iostream>
#include "pch.h"

class HookBase {};

template <uintptr_t offset, typename Func>
class Hook;

template <uintptr_t offset, typename R, typename... Args>
class Hook<offset, R(__thiscall *)(Args...)> {
 public:
  typedef R(__thiscall* Func)(Args...);

  Func& original = original_;

  Hook()
      : offset_(offset),
        original_(decltype(original_)(offset)),
        target_(nullptr),
        hook_trace_info_() {}


  Hook(const Hook&) = delete;
  Hook(Hook&&) = delete;

  void operator=(const Hook&) = delete;
  void operator=(Hook&&) = delete;

  ~Hook() { LhUninstallHook(&hook_trace_info_); }

  void Initialize(void* target) {
    target_ = target;
    std::cout << "Initializing hook at 0x" << std::hex << offset << "[hook function: 0x" << target << ']' << std::endl;
    LhInstallHook(reinterpret_cast<void*>(offset_), target_, nullptr,
                  &hook_trace_info_);

    ULONG acl_entries[1] = {0};
    LhSetExclusiveACL(acl_entries, 1, &hook_trace_info_);
  }


 private:
  uintptr_t offset_;
  Func original_;
  void* target_;
  HOOK_TRACE_INFO hook_trace_info_;
};
