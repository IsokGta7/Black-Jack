#pragma once
#ifndef COLORCONSOLA_H_INCLUDED
#define COLORCONSOLA_H_INCLUDED

#include <iostream>

#ifdef _WIN32
#include <windows.h>

inline std::ostream &aplicar_color(std::ostream &s, WORD atributos) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, atributos);
    return s;
}

inline std::ostream &blue(std::ostream &s) {
    return aplicar_color(s, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

inline std::ostream &red(std::ostream &s) {
    return aplicar_color(s, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

inline std::ostream &green(std::ostream &s) {
    return aplicar_color(s, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

inline std::ostream &yellow(std::ostream &s) {
    return aplicar_color(s, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

inline std::ostream &white(std::ostream &s) {
    return aplicar_color(s, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
#else
constexpr const char *RESET = "\033[0m";

inline std::ostream &blue(std::ostream &s) {
    return s << "\033[36m"; // cian brillante
}

inline std::ostream &red(std::ostream &s) {
    return s << "\033[31m";
}

inline std::ostream &green(std::ostream &s) {
    return s << "\033[32m";
}

inline std::ostream &yellow(std::ostream &s) {
    return s << "\033[33m";
}

inline std::ostream &white(std::ostream &s) {
    return s << RESET;
}
#endif

#endif // COLORCONSOLA_H_INCLUDED
