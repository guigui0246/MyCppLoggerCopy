/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-guillaume.deplaine
** File description:
** exports
*/

#pragma once

#ifdef _WIN32
    #ifdef COMMON_EXPORTS
        #define COMMON_API __declspec(dllexport)
        #define COMMON_NON_SET __declspec(dllimport)
    #else
        #define COMMON_API __declspec(dllimport)
        #define COMMON_NON_SET __declspec(dllexport)
    #endif
#else
    #ifdef COMMON_EXPORTS
        #define COMMON_API __attribute__((visibility("default")))
        #define COMMON_NON_SET __attribute__((visibility("default")))
    #else
        #define COMMON_API
        #define COMMON_NON_SET
    #endif
#endif
