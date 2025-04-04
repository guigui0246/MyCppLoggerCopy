/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-guillaume.deplaine
** File description:
** Logger
*/

#include "Logger.hpp"
#include "critical_error.hpp"

COMMON_API std::mutex Logger::_mutex;
#ifdef _DEBUG
    COMMON_API bool Logger::_show_error = true;
#else
    COMMON_API bool Logger::_show_error = false;
#endif

COMMON_API LogLevel Logger::_log_level = DEFAULT_LOG_LEVEL;
Logger logger;

// Définition du constructeur Logger
Logger::Logger()
{
    int argc;

    #ifdef _WIN32
        LPWSTR cmdLine = GetCommandLineW();
        auto argv = CommandLineToArgvW(cmdLine, &argc);
    #else
        auto argv = get_argv();
        argc = static_cast<int>(argv.size());
    #endif

    for (int i = 1; i < argc; ++i) {
        #ifdef _WIN32
            std::wstring wstr(argv[i]);
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::string arg = converter.to_bytes(wstr);
        #else
            std::string arg = argv[i];
        #endif
        setLogLevelFromArg(arg);
    }
}

// Définition de la méthode static _log
void Logger::_log(const std::string& message, LogLevel level, const std::string &file, const std::string &line) {
    std::lock_guard lock(_mutex);
    LogLevel currentLogLevel = _log_level;
    if (currentLogLevel == LogLevel::NONE)
        return;

    std::time_t t = std::time(nullptr);
    constexpr const char* format = "[%Y-%m-%d %H:%M:%S] : ";
    char time_buffer[40];
    std::strftime(time_buffer, sizeof(time_buffer), format, std::localtime(&t));
    std::string time_string = time_buffer;
    std::string string = time_string + " (" + file + ":" + line + ") : ";

    if (level >= currentLogLevel) {
        switch (level) {
            case LogLevel::DEBUG:
                std::clog << "[DEBUG] " << string << message << std::endl;
                break;
            case LogLevel::INFO:
                std::clog << "[INFO] " << string << message << std::endl;
                break;
            case LogLevel::WARN:
                std::clog << "[WARN] " << string << message << std::endl;
                break;
            case LogLevel::ERROR:
                if (_show_error)
                    show_error(message);
                std::cerr << "[ERROR] " << string << message << std::endl;
                break;
            case LogLevel::FATAL:
                if (_show_error)
                    show_error(message);
                std::cerr << "[FATAL] " << string << message << std::endl;
                break;
            default: break;
        }
    }
}

// Définition de setLogLevel
COMMON_API void Logger::setLogLevel(LogLevel level) {
    _log_level = level;
}

// Définition de setShowError
COMMON_API void Logger::setShowError(bool show) {
    _show_error = show;
}

// Définition de parse_args
COMMON_API void Logger::parse_args(int argc, char **argv) {
    for (int i = 0; i < argc; ++i) {
        setLogLevelFromArg(argv[i]);
    }
}

// Définition de setLogLevelFromArg
COMMON_API void Logger::setLogLevelFromArg(const std::string& arg) {
    std::string argument = arg;
    std::transform(argument.begin(), argument.end(), argument.begin(), [](unsigned char c){ return std::tolower(c); });

    if (argument == "-v0" || argument == "-vnone" || argument == "--logging=none") {
        _log_level = LogLevel::NONE;
    } else if (argument == "-vvvvv" || argument == "-v5" || argument == "-vdebug" || argument == "--logging=debug" || argument == "-vtrace" || argument == "--logging=trace" || argument == "-vall" || argument == "--logging=all") {
        _log_level = LogLevel::DEBUG;
    } else if (argument == "-vvvv" || argument == "-v4" || argument == "-vinfo" || argument == "--logging=info" || argument == "-vnotice" || argument == "--logging=notice") {
        _log_level = LogLevel::INFO;
    } else if (argument == "-vvv" || argument == "-v3" || argument == "-vwarn" || argument == "-vwarning" || argument == "--logging=warn" || argument == "--logging=warning" || argument == "-vimportant" || argument == "--logging=important") {
        _log_level = LogLevel::WARN;
    } else if (argument == "-vv" || argument == "-v2" || argument == "-verr" || argument == "-verror" || argument == "--logging=err" || argument == "--logging=error" || argument == "-vsevere" || argument == "--logging=severe") {
        _log_level = LogLevel::ERROR;
    } else if (argument == "-v" || argument == "-v1" || argument == "-vfatal" || argument == "-vcritical" || argument == "--logging=fatal" || argument == "--logging=critical" || argument == "-vpanic" || argument == "--logging=panic") {
        _log_level = LogLevel::FATAL;
    } else {
        // Ignore
    }
}
