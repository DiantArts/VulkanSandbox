function(add_precompiled_headers interface)

    # =========================================================================
    # STL
    # =========================================================================

    if (ENABLE_STD_PCH)
        target_precompile_headers(
            ${interface}
            INTERFACE
                <concepts>
                # <coroutine> # requires -fcoroutine
                <any>
                <bitset>
                <chrono>
                <compare>
                <csetjmp>
                <csignal>
                <cstdarg>
                <cstddef>
                <cstdlib>
                <ctime>
                # <expected> # c++23
                <functional>
                <initializer_list>
                <optional>
                <source_location>
                <tuple>
                <type_traits>
                <typeindex>
                <typeinfo>
                <utility>
                <variant>
                <version>
                <memory>
                <memory_resource>
                <new>
                <scoped_allocator>
                <cfloat>
                <cinttypes>
                <climits>
                <cstdint>
                <limits>
                <cassert>
                <cerrno>
                <exception>
                <stdexcept>
                <system_error>
                # <stacktrace> # c++ 23
                <cctype>
                <charconv>
                <cstring>
                <cuchar>
                <cwchar>
                <cwctype>
                # <format> # c++ 23
                <string>
                <string_view>
                <array>
                <deque>
                <forward_list>
                <list>
                <map>
                <queue>
                <set>
                <span>
                <stack>
                <unordered_map>
                <unordered_set>
                <vector>
                <iterator>
                <ranges>
                <algorithm>
                # <execution> # linkage errors
                <bit>
                <cfenv>
                <cmath>
                <complex>
                <numbers>
                <numeric>
                <random>
                <ratio>
                <valarray>
                <clocale>
                <codecvt>
                <locale>
                <cstdio>
                <fstream>
                <iomanip>
                <ios>
                <iosfwd>
                <iostream>
                <istream>
                <ostream>
                # <spanstream> # c++ 23
                <sstream>
                <streambuf>
                <syncstream>
                <filesystem>
                <regex>
                <atomic>
                <barrier>
                <condition_variable>
                <future>
                <latch>
                <mutex>
                <semaphore>
                <shared_mutex>
                <stop_token>
                <thread>
        )
    endif ()



    # =========================================================================
    # Personal Headers
    # =========================================================================

    if (ENABLE_PCH)
        target_precompile_headers(
            ${interface}
            INTERFACE
                <pch.hpp>
        )
    endif ()

endfunction()
