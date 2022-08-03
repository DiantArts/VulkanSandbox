#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Log
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::logImpl(
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
    Logger::outputLog(
        filepath,
        functionName,
        lineNumber,
        Logger::Level::none,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
}

///////////////////////////////////////////////////////////////////////////
/// \brief Logs using fmt
///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::logImpl(
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    const Logger::Level level,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
    Logger::outputLog(
        filepath,
        functionName,
        lineNumber,
        level,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Assert
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::assertImpl(
    bool condition,
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
    Logger::outputAssert(
        condition,
        filepath,
        functionName,
        lineNumber,
        Logger::Level::fatalError,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::assertImpl(
    bool condition,
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    const Logger::Level level,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
    Logger::outputAssert(
        condition,
        filepath,
        functionName,
        lineNumber,
        level,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Silent Assert
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::silentAssertImpl(
    bool condition,
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
#if defined(FORCE_PRINT)
    Logger::outputAssert(
        condition,
        filepath,
        functionName,
        lineNumber,
        Logger::Level::fatalError,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
#else
    Logger::outputSilentAssert(
        condition,
        filepath,
        functionName,
        lineNumber,
        Logger::Level::fatalError,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
#endif
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::silentAssertImpl(
    bool condition,
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    const Logger::Level level,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
#if defined(FORCE_PRINT)
    Logger::outputAssert(
        condition,
        filepath,
        functionName,
        lineNumber,
        level,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
#else
    Logger::outputSilentAssert(
        condition,
        filepath,
        functionName,
        lineNumber,
        level,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
#endif
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helper
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::outputLog(
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    const Logger::Level level,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
#if defined(NDEBUG)
    if (level == Logger::Level::debug) {
        return;
    }
#endif // ifdef NDEBUG

    // call position
    auto relaviteFilepath{
        ::std::filesystem::relative(::std::filesystem::path{ filepath }, ".").generic_string()
    };
    if (relaviteFilepath.starts_with("sources/")) {
        relaviteFilepath = relaviteFilepath.substr(8);
    }
    auto callPosition{
        ::fmt::format(::fmt::emphasis::bold,"{}:{}({})", relaviteFilepath, lineNumber, functionName)
    };

    // use message
    auto userMessage{
        ::fmt::format(subformat, ::std::forward<decltype(args)>(args)...)
    };

    // log level
    ::std::string logSpecifier;
    switch (level) {
    case Logger::Level::none: // no extra output. Should be avoided
        ::fmt::print("{}\n", userMessage);
        return;
    case Logger::Level::success: // is successful
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::bg(fmt::color::chartreuse) | ::fmt::fg(fmt::color::black),
            "SUCCESS"
        );
        break;
    case Logger::Level::note: // user driven (configuration operations)
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::fg(fmt::color::gold),
            "note"
        );
        break;
    case Logger::Level::info: // user driven (regularly scheduled operations)
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::fg(fmt::color::aqua),
            "info"
        );
        break;
    case Logger::Level::trace: // tracks potential bugs
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::fg(fmt::color::tomato),
            "trace"
        );
        break;
    case Logger::Level::debug: // (disabled with NDEBUG)
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::fg(fmt::color::fuchsia),
            "debug"
        );
        break;
    case Logger::Level::warning: // can potential become an error
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::fg(fmt::color::red),
            "warning"
        );
        break;
    case Logger::Level::error: // error that cannot be recovered but does not throw
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::bg(fmt::color::red) | ::fmt::fg(fmt::color::black),
            "FAILURE"
        );
        break;
    case Logger::Level::fatal: // error that cannot be recovered, throws an exception
    case Logger::Level::fatalError: // same as fatal
        logSpecifier = ::fmt::format(
            ::fmt::emphasis::bold | ::fmt::bg(fmt::color::red) | ::fmt::fg(fmt::color::black),
            "FAILURE"
        );
        throw ::std::runtime_error{
            ::fmt::format("\n[{}] [{}] [{}] {}", Logger::getDate(), logSpecifier, callPosition, userMessage)
        };
    };

    switch (level) {
    case Logger::Level::none: // no extra output. Should be avoided
    case Logger::Level::success: // is successful
    case Logger::Level::note: // user driven (configuration operations)
    case Logger::Level::info: // user driven (regularly scheduled operations)
        ::fmt::print("[{}] [{}] {}\n", Logger::getDate(), logSpecifier, userMessage);
        break;
    case Logger::Level::trace: // tracks potential bugs
    case Logger::Level::debug: // (disabled with NDEBUG)
    case Logger::Level::warning: // can potential become an error
    case Logger::Level::error: // error that cannot be recovered but does not throw
        ::fmt::print("[{}] [{}] [{}] {}\n", Logger::getDate(), logSpecifier, callPosition, userMessage);
        break;
    };
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::outputAssert(
    const bool condition,
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    Logger::Level level,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
#if defined(PRINT_DEBUG) && defined(NDEBUG)
    if (condition) {
        level = Logger::Level::success;
    } else {
        return;
    }
#elif defined(PRINT_DEBUG)
    if (condition) {
        level = Logger::Level::success;
    }
#elif defined(NDEBUG)
    return;
#else
    if (condition) {
        return;
    }
#endif

    Logger::outputLog(
        filepath,
        functionName,
        lineNumber,
        level,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Args
> void ::xrn::Logger::outputSilentAssert(
    const bool condition,
    const ::std::string_view filepath,
    const ::std::string_view functionName,
    const ::std::size_t lineNumber,
    Logger::Level level,
    const ::fmt::format_string<Args...> subformat,
    Args&&... args
)
{
#if defined(NDEBUG)
    return;
#endif

    if (condition) {
        return;
    }

    Logger::outputLog(
        filepath,
        functionName,
        lineNumber,
        level,
        subformat,
        ::std::forward<decltype(args)>(args)...
    );
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::Logger::getDate()
    -> ::std::string
{
    std::time_t t = ::std::time(0);   // get time now
    std::tm* now = ::std::localtime(&t);
    ::std::string output;

    // month
    if (now->tm_mon < 10) {
        output += '0';
    }
    output += ::std::to_string(now->tm_mon + 1);
    output += '-';

    // day
    if (now->tm_mday < 10) {
        output += '0';
    }
    output += ::std::to_string(now->tm_mday);
    output += ' ';

    // hour
    if (now->tm_hour < 10) {
        output += '0';
    }
    output += ::std::to_string(now->tm_hour);
    output += ':';

    // min
    if (now->tm_min < 10) {
        output += '0';
    }
    output += ::std::to_string(now->tm_min);
    output += ':';

    // sec
    if (now->tm_sec < 10) {
        output += '0';
    }
    output += ::std::to_string(now->tm_sec);
    output += '.';

    // ms
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(ms);
    ms -= seconds;
    if (ms < 10ms) {
        output += "00";
    } else if (ms < 100ms) {
        output += '0';
    }
    output += ::std::to_string(ms.count());

    return output;
}
