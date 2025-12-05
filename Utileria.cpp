#include "Utileria.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <cctype>
#include <iterator>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#else
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

#include "ColorConsola.h"

namespace {

AnimacionConfig g_animConfig{true, 12};

bool EsValorDesactivado(const std::string &valor) {
    std::string lower;
    lower.reserve(valor.size());
    std::transform(valor.begin(), valor.end(), std::back_inserter(lower), [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return lower == "0" || lower == "off" || lower == "false" || lower == "none";
}

} // namespace

void MoverCursor(short x, short y) {
#ifdef _WIN32
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
#endif
    set_cursor(false);
}

void CambiarTamanio(int w, int h) {
#ifdef _WIN32
    HWND console = GetConsoleWindow();
    RECT r{};
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, w, h, TRUE);
#else
    (void)w;
    (void)h;
#endif
}

void DibujarMarco(int w, int h, int x, int y) {
    MoverCursor(x, y);
    std::cout << BOX_TOP_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_HORIZONTAL;
    std::cout << BOX_TOP_RIGHT << std::endl;

    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << BOX_VERTICAL;
        MoverCursor(x + w + 1, y);
        std::cout << BOX_VERTICAL;
    }

    MoverCursor(x, ++y);
    std::cout << BOX_BOTTOM_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_HORIZONTAL;
    std::cout << BOX_BOTTOM_RIGHT << std::endl;
}

void DibujarMarcoSolido(int w, int h, int x, int y) {
    MoverCursor(x, y);
    std::cout << BOX_TOP_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_HORIZONTAL;
    std::cout << BOX_TOP_RIGHT << std::endl;

    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << BOX_VERTICAL;
        for (int m = 0; m < w; m++) std::cout << " ";
        std::cout << BOX_VERTICAL;
    }

    MoverCursor(x, ++y);
    std::cout << BOX_BOTTOM_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_HORIZONTAL;
    std::cout << BOX_BOTTOM_RIGHT << std::endl;
}

void BorrarMarco(int w, int h, int x, int y) {
    MoverCursor(x, y);
    for (int n = -1; n <= w; n++) std::cout << " ";

    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << " ";
        MoverCursor(x + w + 1, y);
        std::cout << " ";
        std::cout << std::endl;
    }

    MoverCursor(x, ++y);
    for (int n = -1; n <= w; n++) std::cout << " ";
}

int * CrearArreglo(int dim) {
    if (dim <= 0) {
        throw std::invalid_argument("La dimensión del arreglo debe ser positiva");
    }
    int * ary = new int[dim];
    for (int i = 0; i < dim; i++) {
        ary[i] = 0;
    }
    return ary;
}

void DestruirArreglo(int * & ary) {
    delete[] ary;
    ary = nullptr;
}

void set_cursor(bool visible) {
#ifdef _WIN32
    CONSOLE_CURSOR_INFO info{};
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
#else
    if (visible) {
        std::cout << "\033[?25h";
    } else {
        std::cout << "\033[?25l";
    }
#endif
}

void LimpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}

void ActualizarTitulo(const std::string &titulo) {
#ifdef _WIN32
    SetConsoleTitleA(titulo.c_str());
#else
    std::cout << "\033]0;" << titulo << "\007";
#endif
}

void ConfigurarCodificacion() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);
#endif
}

AnimacionConfig ObtenerConfiguracionAnimacion() {
    return g_animConfig;
}

void EstablecerAnimacionesHabilitadas(bool habilitar) {
    g_animConfig.habilitada = habilitar;
}

void ConfigurarAnimacionesDesdeEntorno() {
    const char *envAnim = std::getenv("BJ_ANIMATIONS");
    if (envAnim && EsValorDesactivado(envAnim)) {
        g_animConfig.habilitada = false;
    }
    if (std::getenv("BJ_DISABLE_ANIMATIONS")) {
        g_animConfig.habilitada = false;
    }

    const char *envDelay = std::getenv("BJ_ANIMATION_DELAY_MS");
    if (envDelay) {
        try {
            g_animConfig.retardoPasoMs = std::max(1, std::stoi(envDelay));
        } catch (const std::exception &) {
        }
    }
}

void AnimarAparicionRectangular(int x, int y, int w, int h) {
    if (!g_animConfig.habilitada) return;

    const char *rellenos[] = {u8"░", u8"▒", u8"▓"};
    for (int fila = 0; fila < h; ++fila) {
        MoverCursor(x, y + fila);
#ifndef _WIN32
        int color = 255 - (fila % 4) * 3;
        std::cout << "\033[48;5;" << color << "m";
#endif
        const char *relleno = rellenos[fila % 3];
        for (int col = 0; col < w; ++col) std::cout << relleno;
#ifndef _WIN32
        std::cout << RESET;
#endif
        EsperarMilisegundos(g_animConfig.retardoPasoMs);
    }
}

void EsperarMilisegundos(int milisegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milisegundos));
}

int LeerTecla() {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int codigoExtendido = _getch();
        return TraducirCodigoExtendidoWindows(ch, codigoExtendido);
    }
    if (ch == '\r') {
        return ENTER;
    }
    return ch;
#else
    termios oldt{};
    if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
        return getchar();
    }

    termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch = getchar();
    if (ch == 27) { // Secuencia de escape para flechas ANSI
        int next1 = getchar();
        if (next1 == '[') {
            int next2 = getchar();
            switch (next2) {
            case 'A':
                ch = UP;
                break;
            case 'B':
                ch = DOWN;
                break;
            case 'C':
                ch = RIGHT;
                break;
            case 'D':
                ch = LEFT;
                break;
            default:
                break;
            }
        }
    } else if (ch == '\n') {
        ch = ENTER;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

TerminalSize ObtenerTamanoTerminal() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return {width, height};
    }
    return {220, 60};
#else
    winsize w{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0 && w.ws_row > 0) {
        return {static_cast<int>(w.ws_col), static_cast<int>(w.ws_row)};
    }
    const char *envCols = std::getenv("COLUMNS");
    const char *envRows = std::getenv("LINES");
    if (envCols && envRows) {
        try {
            return {std::stoi(envCols), std::stoi(envRows)};
        } catch (const std::exception &) {
        }
    }
    return {220, 60};
#endif
}

int CentrarEnDimension(int dimensionTotal, int dimensionContenido) {
    if (dimensionContenido >= dimensionTotal) {
        return 0;
    }
    return (dimensionTotal - dimensionContenido) / 2;
}
