#pragma once
#include <iosfwd>
#include <string>

enum class ConsoleColor {
    Default,
    Blue,
    Red,
    Green,
    Yellow,
    White
};

class Console {
public:
    static Console & instance();

    void move_cursor(short x, short y);
    void set_window_size(int w, int h);
    void set_cursor_visible(bool visible);
    void set_title(const std::string & title);
    bool supports_virtual_terminal() const;

    void write(const std::wstring & text);
    std::ostream & apply_color(std::ostream & os, ConsoleColor color);

private:
    Console();

    bool vtEnabled_ = false;
#ifdef _WIN32
    void apply_attribute_color(ConsoleColor color);
    void restore_attributes();
    void enable_virtual_terminal();

    void * output_ = nullptr;
    unsigned short defaultAttributes_ = 0;
#endif
};

