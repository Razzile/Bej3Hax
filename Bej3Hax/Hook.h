#pragma once
#include <easyhook.h>
#include <spdlog/spdlog.h>

#include <functional>

#include "pch.h"

template <typename Func>
class Hook;

class HookBase {
 public:
  HookBase(uintptr_t offset)
      : offset_(offset), target_(nullptr), hook_trace_info_() {}

  HookBase(const HookBase&) = delete;

  void operator=(const HookBase&) = delete;

  HookBase& operator=(HookBase&& other) noexcept {
    this->target_ = other.target_;
    this->offset_ = other.offset_;
    this->hook_trace_info_ = other.hook_trace_info_;

    return *this;
  }

  ~HookBase() { LhUninstallHook(&hook_trace_info_); }

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

template <typename R, typename... Args>
class Hook<R(__thiscall*)(Args...)> : public HookBase {
 public:
  typedef R(__thiscall* Func)(Args...);

  Func original = nullptr;

  Hook(uintptr_t offset)
      : HookBase(offset), original(decltype(original)(offset)) {}

  Hook(Hook&& other) noexcept : HookBase(std::move(other)) {
    this->original = other.original;
  }

  Hook& operator=(Hook&& other) noexcept {
    HookBase::operator=(std::move(other));
    this->original = other.original;

    return *this;
  }
};

template <typename R, typename... Args>
class Hook<R(__stdcall*)(Args...)> : public HookBase {
 public:
  typedef R(__stdcall* Func)(Args...);

  Func original = nullptr;

  Hook(uintptr_t offset)
      : HookBase(offset), original(decltype(original)(offset)) {}

  Hook(Hook&& other) noexcept : HookBase(std::move(other)) {
    this->original = other.original;
  }

  Hook& operator=(Hook&& other) noexcept {
    HookBase::operator=(std::move(other));
    this->original = other.original;

    return *this;
  }
};

template <typename R, typename... Args>
class Hook<R(__fastcall*)(Args...)> : public HookBase {
 public:
  typedef R(__fastcall* Func)(Args...);

  Func original = nullptr;

  Hook(uintptr_t offset)
      : HookBase(offset), original(decltype(original)(offset)) {}

  Hook(Hook&& other) noexcept : HookBase(std::move(other)) {
    this->original = other.original;
  }

  Hook& operator=(Hook&& other) noexcept {
    HookBase::operator=(std::move(other));
    this->original = other.original;

    return *this;
  }
};

template <typename R, typename... Args>
class Hook<R(__cdecl*)(Args...)> : public HookBase {
 public:
  typedef R(__cdecl* Func)(Args...);

  Func original = nullptr;

  Hook(uintptr_t offset)
      : HookBase(offset), original(decltype(original)(offset)) {}

  Hook(Hook&& other) noexcept : HookBase(std::move(other)) {
    this->original = other.original;
  }

  Hook& operator=(Hook&& other) noexcept {
    HookBase::operator=(std::move(other));
    this->original = other.original;

    return *this;
  }
};
