#pragma once
#include "pch.h"

#include <easyhook.h>
#include <spdlog/spdlog.h>

#include <functional>

template <uintptr_t offset, typename Func>
class Hook;

class HookBase {
public:
  HookBase(uintptr_t offset)
    : offset_(offset),
      target_(nullptr),
      hook_trace_info_() {
  }

  HookBase(const HookBase&) = delete;
  HookBase(HookBase&&) = delete;

  void operator=(const HookBase&) = delete;
  void operator=(HookBase&&) = delete;

  ~HookBase() {
    LhUninstallHook(&hook_trace_info_);
  }

  void Initialize(void* target) {
    target_ = target;
    spdlog::info("Initializing hook at 0x{0:x} [hook function: {1}]", offset_,
                 target);

    LhInstallHook(reinterpret_cast<void*>(offset_), target_, nullptr,
                  &hook_trace_info_);

    ULONG acl_entries[1] = {0};
    LhSetExclusiveACL(acl_entries, 1, &hook_trace_info_);
  }

private:
  uintptr_t offset_;
  void* target_;
  HOOK_TRACE_INFO hook_trace_info_;
};


template <uintptr_t offset, typename R, typename... Args>
class Hook<offset, R(__thiscall*)(Args ...)> : public HookBase {
public:
  typedef R (__thiscall* Func)(Args ...);

  Func original = nullptr;

  Hook()
    : HookBase(offset),
      original(decltype(original)(offset)) {
  }
};

template <uintptr_t offset, typename R, typename... Args>
class Hook<offset, R(__stdcall*)(Args...)> : public HookBase {
 public:
  typedef R(__stdcall* Func)(Args...);

  Func original = nullptr;

  Hook() : HookBase(offset), original(decltype(original)(offset)) {}
};

template <uintptr_t offset, typename R, typename... Args>
class Hook<offset, R(__fastcall*)(Args...)> : public HookBase {
 public:
  typedef R(__fastcall* Func)(Args...);

  Func original = nullptr;

  Hook() : HookBase(offset), original(decltype(original)(offset)) {}
};

template <uintptr_t offset, typename R, typename... Args>
class Hook<offset, R(__cdecl*)(Args...)> : public HookBase {
 public:
  typedef R(__cdecl* Func)(Args...);

  Func original = nullptr;

  Hook() : HookBase(offset), original(decltype(original)(offset)) {}
};
