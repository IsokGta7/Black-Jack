#include "Console.h"

#include <codecvt>
#include <iostream>
#include <locale>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace {
std::string AnsiColor(ConsoleColor color) {
    switch (color) {
    case ConsoleColor::Blue:
        return "\x1b[96m";
    case ConsoleColor::Red:
        return "\x1b[91m";
    case ConsoleColor::Green:
        return "\x1b[92m";
    case ConsoleColor::Yellow:
        return "\x1b[93m";
    case ConsoleColor::White:
        return "\x1b[97m";
    case ConsoleColor::Default:
    default:
        return "\x1b[39m";
    }
}
}

Console & Console::instance() {
    static Console console;
    return console;
}

Console::Console() {
#ifdef _WIN32
    output_ = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    if (output_ && GetConsoleScreenBufferInfo((HANDLE) output_, & bufferInfo)) {
        defaultAttributes_ = bufferInfo.wAttributes;
    }
    enable_virtual_terminal();
#else
    vtEnabled_ = true;
#endif
}

void Console::move_cursor(short x, short y) {
#ifdef _WIN32
    if (!vtEnabled_ && output_) {
        COORD coord = {
            x,
            y
        };
        SetConsoleCursorPosition((HANDLE) output_, coord);
        return;
    }
#endif
    std::cout << "\x1b[" << (y + 1) << ";" << (x + 1) << "H";
}

void Console::set_window_size(int w, int h) {
#ifdef _WIN32
    HWND console = GetConsoleWindow();
    if (console != NULL) {
        RECT r;
        if (GetWindowRect(console, & r)) {
            MoveWindow(console, r.left, r.top, w, h, TRUE);
        }
    }
#else
    (void) w;
    (void) h;
#endif
}

void Console::set_cursor_visible(bool visible) {
#ifdef _WIN32
    if (!vtEnabled_ && output_) {
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = visible;
        SetConsoleCursorInfo((HANDLE) output_, & info);
        return;
    }
#endif
    std::cout << (visible ? "\x1b[?25h" : "\x1b[?25l");
}

void Console::set_title(const std::string & title) {
#ifdef _WIN32
    if (!vtEnabled_) {
        SetConsoleTitleA(title.c_str());
        return;
    }
#endif
    std::cout << "\x1b]0;" << title << "\x07";
}

bool Console::supports_virtual_terminal() const {
    return vtEnabled_;
}

void Console::write(const std::wstring & text) {
#ifdef _WIN32
    DWORD written = 0;
    if (output_ && GetFileType((HANDLE) output_) == FILE_TYPE_CHAR &&
        WriteConsoleW((HANDLE) output_, text.c_str(), (DWORD) text.size(), & written, nullptr)) {
        return;
    }
#endif
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > converter;
    std::cout << converter.to_bytes(text);
}

std::ostream & Console::apply_color(std::ostream & os, ConsoleColor color) {
#ifdef _WIN32
    if (!vtEnabled_) {
        apply_attribute_color(color);
        return os;
    }
#endif
    os << AnsiColor(color);
    return os;
}

#ifdef _WIN32
void Console::apply_attribute_color(ConsoleColor color) {
    if (!output_) return;

    WORD attributes = defaultAttributes_;
    switch (color) {
    case ConsoleColor::Blue:
        attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::Red:
        attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::Green:
        attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::Yellow:
        attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::White:
        attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::Default:
    default:
        attributes = defaultAttributes_;
        break;
    }
    SetConsoleTextAttribute((HANDLE) output_, attributes);
}

void Console::enable_virtual_terminal() {
    if (!output_) return;

    DWORD mode = 0;
    if (GetConsoleMode((HANDLE) output_, & mode)) {
        DWORD desired = mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (SetConsoleMode((HANDLE) output_, desired)) {
            vtEnabled_ = true;
        }
    }
}
#endif

