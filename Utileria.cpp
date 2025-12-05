#include "Utileria.h"

#include <chrono>
#include <cstdio>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#else
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#endif

#include "ColorConsola.h"

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
