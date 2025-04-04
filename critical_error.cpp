/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-bsrtype-guillaume.deplaine
** File description:
** error
*/

#ifdef _WIN32
    #include <Windows.h>
#endif

#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include "critical_error.hpp"

std::map<std::string, bool> error_window_open;
std::mutex error_mutex;

static void show_error_no_graphics(const std::string& message)
{
    #ifdef _WIN32
        const std::wstring wMessage(message.begin(), message.end());
        MessageBoxW(NULL, wMessage.c_str(), L"Error", MB_ICONERROR | MB_OK);
    #else
        if (std::system("kdialog --version > /dev/null 2>&1") == 0) {
            std::string command = "kdialog --error \"" + message + "\"";
            std::system(command.c_str());
        } else if (std::system("zenity --version > /dev/null 2>&1") == 0) {
            std::string command = "zenity --error --text=\"" + message + "\"";
            std::system(command.c_str());
        }
    #endif
    std::lock_guard lock(error_mutex);
    error_window_open[message] = false;
}

void show_error(const std::string& message)
{
    std::lock_guard lock(error_mutex);
    if (error_window_open[message])
        return;
    error_window_open[message] = true;
    std::thread error(show_error_no_graphics, message);
    error.detach();
}
