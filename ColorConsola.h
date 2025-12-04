#pragma once
#ifndef COLORCONSOLA_H_INCLUDED
#define COLORCONSOLA_H_INCLUDED

#include <ostream>

#include "Console.h"

inline std::ostream & apply_console_color(std::ostream & s, ConsoleColor color) {
    return Console::instance().apply_color(s, color);
}

inline std::ostream & blue(std::ostream & s) {
    return apply_console_color(s, ConsoleColor::Blue);
}

inline std::ostream & red(std::ostream & s) {
    return apply_console_color(s, ConsoleColor::Red);
}

inline std::ostream & green(std::ostream & s) {
    return apply_console_color(s, ConsoleColor::Green);
}

inline std::ostream & yellow(std::ostream & s) {
    return apply_console_color(s, ConsoleColor::Yellow);
}

inline std::ostream & white(std::ostream & s) {
    return apply_console_color(s, ConsoleColor::White);
}

inline std::ostream & reset(std::ostream & s) {
    return apply_console_color(s, ConsoleColor::Default);
}

#endif // COLORCONSOLA_H_INCLUDED
