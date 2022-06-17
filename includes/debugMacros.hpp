/*
** EPITECH PROJECT, 2020
** macros
** File description:
** macros of the program
*/

#ifndef MACROS_HPP
#define MACROS_HPP

#include <mutex>
#include <chrono>
#include <iostream>

#if DEBUG > 0

inline::std::recursive_mutex debugClogMutex;
inline int isDebugClogMutexLocked = 0;
inline::std::string str;

#define NESTED_DEBUG_MSG(message) { \
   ::std::lock_guard<std::recursive_mutex> debugClogLockGuard(debugClogMutex); \
    if (isDebugClogMutexLocked == 1) { \
       ::std::clog << "\n"; \
        isDebugClogMutexLocked--; \
    } \
   ::std::clog << "[" << __FILE__ << ":" << __LINE__ << "]"; \
    if (isDebugClogMutexLocked == 1) { \
       ::std::clog << " - "; \
    } \
    ++isDebugClogMutexLocked; \
    auto msg = message; \
    isDebugClogMutexLocked = (!isDebugClogMutexLocked) ? 0 : isDebugClogMutexLocked - 1; \
    if (!isDebugClogMutexLocked) { \
       ::std::clog << "[" << __FILE__ << ":" << __LINE__ << "] - "; \
    } \
   ::std::clog << msg << "\n"; \
}

#define DEBUG_MSG(message) { \
   ::std::lock_guard<std::recursive_mutex> debugClogLockGuard(debugClogMutex); \
    if (isDebugClogMutexLocked == 1) { \
       ::std::clog << "\n"; \
        isDebugClogMutexLocked--; \
    } \
    ++isDebugClogMutexLocked; \
   ::std::clog << "[" << __FILE__ << ":" << __LINE__ << "] - " << message << "\n"; \
    isDebugClogMutexLocked--; \
}

#define DEBUG_FUNC  { \
   ::std::lock_guard<std::recursive_mutex> debugClogLockGuard(debugClogMutex); \
    if (isDebugClogMutexLocked == 1) { \
       ::std::clog << "\n"; \
        isDebugClogMutexLocked--; \
    } \
    ++isDebugClogMutexLocked; \
   ::std::clog << '[' << __FILE__ << ':' << __LINE__ << "] (" << __FUNCTION__ << ")" \
              <<::std::endl; \
    isDebugClogMutexLocked--; \
}

#define DEBUG_PRETTY_FUNC  { \
   ::std::lock_guard<std::recursive_mutex> debugClogLockGuard(debugClogMutex); \
    if (isDebugClogMutexLocked == 1) { \
       ::std::clog << "\n"; \
        isDebugClogMutexLocked--; \
    } \
    ++isDebugClogMutexLocked; \
   ::std::clog << '[' << __FILE__ << ':' << __LINE__ << "] (" << __PRETTY_FUNCTION__ \
              << ")" <<::std::endl; \
    isDebugClogMutexLocked--; \
}

#if DEBUG > 1
namespace debuging {
class check_time {
public:
    check_time(const ::std::string file, const ::std::string function, const int line)
        : m_ClockStart(::std::chrono::high_resolution_clock::now())
        , m_File(file), m_Function(function), m_Line(line)
    {
       ::std::lock_guard<std::recursive_mutex> debugClogLockGuard(debugClogMutex);

        if (isDebugClogMutexLocked == 1) {
           ::std::clog << "\n";
            isDebugClogMutexLocked--;
        }
       ::std::clog << "[" << m_File << ":" << m_Line << "] (" << m_Function << ")\n";
    }

    ~check_time()
    {
        m_ClockEnd =::std::chrono::high_resolution_clock::now();

       ::std::clog << "[" << m_File << ":" << m_Line << "] (" << m_Function << ") - "
                  << ::std::chrono::duration<float> (m_ClockEnd - m_ClockStart).count() * 1000.0f
                  << "ms\n";
        isDebugClogMutexLocked = false;
    }

private:
   ::std::chrono::time_point<std::chrono::high_resolution_clock> m_ClockStart, m_ClockEnd;
   ::std::string m_File, m_Function;
    int m_Line;
};
} // namespace debuging
#define DEBUG_TIME debuging::check_time checking_time_class(__FILE__, __FUNCTION__, __LINE__)


#else // DEBUG > 1


namespace debuging {
class check_time {
public:
    check_time(const ::std::string file, const ::std::string function, const int line)
        : m_File(file), m_Function(function), m_Line(line)
    {
       ::std::lock_guard<std::recursive_mutex> debugClogLockGuard(debugClogMutex);

        if (isDebugClogMutexLocked == 1) {
           ::std::clog << "\n";
            isDebugClogMutexLocked--;
        }
       ::std::clog << "[" << m_File << ":" << m_Line << "] (" << m_Function << ")\n";
    }

    ~check_time()
    {
       ::std::lock_guard<std::recursive_mutex> debugClogLockGuard(debugClogMutex);

       ::std::clog << "[" << m_File << ":" << m_Line << "] (" << m_Function << ") - Exit\n";
    }

private:
   ::std::string m_File, m_Function;
    int m_Line;
};
}
#define DEBUG_TIME debuging::check_time checking_time_class(__FILE__, __FUNCTION__, __LINE__)
#endif // DEBUG > 1

#else // DEBUG > 0

#define DEBUG_MSG(message)
#define DEBUG_FUNC
#define DEBUG_PRETTY_FUNC
#define DEBUG_TIME


#endif // DEBUG > 0


#define ERROR_MSG(message) ::std::cerr << "ERROR [" << __FILE__ << ':' << __LINE__ << ']' \
    << " - " << message <<::std::endl

#define THROW_MSG(throwMsg)::std::cerr << "[" << __FILE__ << ':' << __LINE__ << ']' <<::std::endl, \
    throw throwMsg,

#endif // MACROS_HPP
