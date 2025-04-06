/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-guillaume.deplaine
** File description:
** Logger
*/

#ifndef LOGGING_HPP_
    #define LOGGING_HPP_


    #ifdef MSVC
        #pragma warning(push)
        #pragma warning(disable : 0)
    #elif defined(__GNUC__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wall"
        #pragma GCC diagnostic ignored "-Wextra"
        #pragma GCC diagnostic ignored "-Wunknown-pragmas"
        #pragma GCC diagnostic ignored "-Wunused-function"
        #pragma GCC diagnostic ignored "-Wunused-result"
    #elif defined(__clang__)
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wall"
        #pragma clang diagnostic ignored "-Wextra"
        #pragma clang diagnostic ignored "-Wunknown-pragmas"
        #pragma clang diagnostic ignored "-Wunused-function"
        #pragma clang diagnostic ignored "-Wunused-result"
        #endif /* MSVC */


    #include <iostream>
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <mutex>
    #include "./tools.hpp"
    #include "./exports.hpp"

    #ifdef _WIN32
        #include <Windows.h>
        #include <shellapi.h>
    #else
        #include <unistd.h>
    #endif

#undef NONE
#undef DEBUG
#undef INFO
#undef WARN
#undef ERROR
#undef FATAL
// Enum pour les niveaux de logging
#undef ERROR
enum class LogLevel {
    NONE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

#ifndef DEFAULT_LOG_LEVEL
    #ifdef _DEBUG
        #define DEFAULT_LOG_LEVEL LogLevel::DEBUG
    #else
        #define DEFAULT_LOG_LEVEL LogLevel::WARN
    #endif
#endif

#ifndef _WIN32
    static std::vector<std::string> get_argv() {
        for (char **env = environ; *env != nullptr; ++env) {
            if (std::string(*env).starts_with("ARGS=")) {
                std::string args = std::string(*env).substr(5); // Get the argument string
                std::vector<std::string> arg = split(args, ' ');
                return arg;
            }
        }
        return {};
    }
#endif /* !_WIN32 */

#include <locale>
#include <codecvt>

class COMMON_API Logger {
    public:
        Logger();

        static void _log(const std::string& message, LogLevel level, const std::string &file, const std::string &line);
        static void setLogLevel(LogLevel level);
        static void setShowError(bool show);
        static void parse_args(int argc, char **argv);

    protected:
        static void setLogLevelFromArg(const std::string& arg);

    private:
        static std::mutex _mutex;
        static LogLevel _log_level;
        static bool _show_error;
};


#undef __needs_log_redefinition
#define _needs_log_redefinition

    #ifdef MSVC
        #pragma warning(pop)
    #elif defined(__GNUC__)
        #pragma GCC diagnostic pop
    #elif defined(__clang__)
        #pragma clang diagnostic pop
    #endif /* MSVC */

#endif /* !LOGGING_HPP_ */

#ifdef _needs_log_redefinition
    #undef _needs_log_redefinition
    #undef logEngine
    #undef debug
    #undef trace
    #undef info
    #undef notice
    #undef warn
    #undef important
    #undef err
    #undef severe
    #undef fatal
    #undef fatal_error
    #undef critical
    #undef critical_error
    #undef panic
    #define logEngine(message, level) Logger::_log(message, level, __FILE__, std::to_string(__LINE__))
    #define debug(message) logEngine(message, LogLevel::DEBUG)
    #define trace(message) logEngine(message, LogLevel::DEBUG)
    #define info(message) logEngine(message, LogLevel::INFO)
    #define notice(message) logEngine(message, LogLevel::INFO)
    #define warn(message) logEngine(message, LogLevel::WARN)
    #define important(message) logEngine(message, LogLevel::WARN)
    #define err(message) logEngine(message, LogLevel::ERROR)
    #define severe(message) logEngine(message, LogLevel::ERROR)
    #define fatal(message) logEngine(message, LogLevel::FATAL)
    #define fatal_error(message) logEngine(message, LogLevel::FATAL)
    #define critical(message) logEngine(message, LogLevel::FATAL)
    #define critical_error(message) logEngine(message, LogLevel::FATAL)
    #define panic(message) logEngine(message, LogLevel::FATAL)
#endif /* _needs_log_redefinition */
