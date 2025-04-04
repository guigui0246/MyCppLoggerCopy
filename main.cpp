#include "Logger.hpp"

int main(int argc, char **argv) {
    // Example usage of Logger class
    Logger::parse_args(argc, argv);
    Logger::setLogLevel(LogLevel::DEBUG);
    Logger::setShowError(true);

    debug("This is a debug message.");
    info("This is an info message.");
    warn("This is a warning message.");
    err("This is an error message.");
    fatal("This is a fatal message.");

    Logger::setShowError(false);
    Logger::setLogLevel(LogLevel::ERROR);
    debug("This is a debug message that doesn't get printed.");
    info("This is an info message that doesn't get printed.");
    warn("This is a warning message that doesn't get printed.");
    err("This is an error message that does get printed.");
    fatal("This is a fatal message that does get printed.");

    return 0;
}
