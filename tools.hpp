/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-guillaume.deplaine
** File description:
** tools
*/

#ifndef TOOLS_HPP_
    #define TOOLS_HPP_

    #include <ostream>
    #include <cstdint>
    #include <sstream>
    #include <string>
    #include <vector>

template <typename T>
std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

using color_t = uint8_t;

color_t constexpr WHITE = 0;
color_t constexpr BLACK = 30;
color_t constexpr RED = 31;
color_t constexpr GREEN = 32;
color_t constexpr YELLOW = 33;
color_t constexpr BLUE = 34;
color_t constexpr MAGENTA = 35;
color_t constexpr CYAN = 36;
color_t constexpr LIGHT_GRAY = 37;
color_t constexpr DARK_GRAY = 90;
color_t constexpr LIGHT_RED = 91;
color_t constexpr LIGHT_GREEN = 92;
color_t constexpr LIGHT_YELLOW = 93;
color_t constexpr LIGHT_BLUE = 94;
color_t constexpr LIGHT_MAGENTA = 95;
color_t constexpr LIGHT_CYAN = 96;
color_t constexpr DEFAULT = 39;

static std::ostream &operator<<(std::ostream &os, const color_t &color) {
    os << "\033[" << static_cast<int>(color) << "m";
    return os;
}

static std::vector<std::string> split(const std::string& str, const char delimiter = ' ', const char comment = '#') {
    std::vector<std::string> tokens;
    size_t end_of_string = str.find_first_of(comment);
    std::string string = str.substr(0, end_of_string);
    string.erase(string.find_last_not_of(" \n\r\t") + 1);
    string.erase(0, string.find_first_not_of(" \n\r\t"));
    end_of_string = string.size();
    size_t start = 0;
    size_t end = string.find(delimiter);
    while (end < end_of_string) {
        tokens.push_back(string.substr(start, end - start));
        start = end + 1;
        end = string.find(delimiter, start);
    }
    if (start < end_of_string)
        tokens.push_back(string.substr(start, end_of_string - start));
    return tokens;
}

template <typename T>
T convert(const std::string& str) {
    std::istringstream ss(str);
    T value;
    ss >> value;
    return value;
}

template<typename T>
std::string join(const std::vector<T>& elements, const std::string& delimiter) {
    std::ostringstream result;
    for (size_t i = 0; i < elements.size(); ++i) {
        result << elements[i];
        if (i != elements.size() - 1) {
            result << delimiter;
        }
    }
    return result.str();
}

template<typename T>
T join(const std::vector<T>& elements, const T& delimiter) {
    T result;
    for (size_t i = 0; i < elements.size(); ++i) {
        result += elements[i];
        if (i != elements.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

#ifdef _WIN32

#include <windows.h>

static std::wstring convertToWideString(const std::string& str) {
    // Convert `std::string` to `std::wstring`
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
    return wstr;
}

static std::string convertFromWideString(const std::wstring& wstr) {
    // Convert `std::wstring` to `std::string`
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string str(size_needed - 1, 0); // -1 to exclude the null terminator
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size_needed, NULL, NULL);
    return str;
}

#endif /* _WIN32 */

#endif /* !TOOLS_HPP_ */
