/*
Created by @PieroCastillo on 2026-04-16
*/
#ifndef TILAPIA_RUNTIME_COMMON_HPP
#define TILAPIA_RUNTIME_COMMON_HPP

#if defined(_MSC_VER)
#define ForceInline __forceinline
#elif defined(__clang__)
#define ForceInline __attribute__((always_inline)) inline
#elif defined(__GNUC__)
#define ForceInline __attribute__((always_inline)) inline
#else
#define ForceInline inline
#endif

#ifdef _INTELLISENSE
    #include <any>
    #include <array>
    #include <algorithm>
    #include <atomic>
    #include <bit>
    #include <concepts>
    #include <cstdint>
    #include <cstdlib>
    #include <condition_variable>
    #include <expected>
    #include <filesystem>
    #include <functional>
    #include <iostream>
    #include <limits>
    #include <map>
    #include <memory>
    #include <memory_resource>
    #include <mutex>
    #include <optional>
    #include <print>
    #include <queue>
    #include <span>
    #include <stdexcept>
    #include <string>
    #include <string_view>
    #include <tuple>
    #include <thread>
    #include <type_traits>
    #include <unordered_map>
    #include <utility>
    #include <variant>
    #include <vector>
#endif

#endif // TILAPIA_RUNTIME_COMMON_HPP