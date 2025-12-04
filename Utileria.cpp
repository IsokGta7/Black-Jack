#include <iostream>
#include <string>

#include "Console.h"
#include "Utileria.h"
#include "ColorConsola.h"

namespace {
std::wstring Single(wchar_t ch) {
    return std::wstring(1, ch);
}
}

void MoverCursor(short x, short y) {
    Console::instance().move_cursor(x, y);
    set_cursor(false);
}

void CambiarTamanio(int w, int h) {
    Console::instance().set_window_size(w, h);
}

void DibujarMarco(int w, int h, int x, int y) {
    auto & console = Console::instance();

    MoverCursor(x, y);
    console.write(Single(ESI));
    for (int n = 0; n < w; n++) console.write(Single(BH));
    console.write(Single(ESD));
    std::cout << std::endl;
    //Impresion del resto del marco menos la ultima linea
    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        console.write(Single(BV));
        MoverCursor(x + w + 1, y);
        console.write(Single(BV));
    }
    //Movemos el cursor a ++y para imprimir la ultima linea del marco.
    MoverCursor(x, ++y);
    console.write(Single(EII));
    for (int n = 0; n < w; n++) console.write(Single(BH));
    console.write(Single(EID));
    std::cout << std::endl;
}

void DibujarMarcoSolido(int w, int h, int x, int y) {
    auto & console = Console::instance();

    MoverCursor(x, y);
    console.write(Single(ESI));
    for (int n = 0; n < w; n++) console.write(Single(BH));
    console.write(Single(ESD));
    std::cout << std::endl;
    //Impresion del resto del marco menos la ultima linea
    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        console.write(Single(BV));
        for (int m = 0; m < w; m++) std::cout << " ";
        console.write(Single(BV));
    }
    //Movemos el cursor a ++y para imprimir la ultima linea del marco.
    MoverCursor(x, ++y);
    console.write(Single(EII));
    for (int n = 0; n < w; n++) console.write(Single(BH));
    console.write(Single(EID));
    std::cout << std::endl;
}

void BorrarMarco(int w, int h, int x, int y) {
    MoverCursor(x, y);
    for (int n = -1; n <= w; n++) std::cout << " ";
    //Impresion del resto del marco menos la ultima linea
    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << " ";
        MoverCursor(x + w + 1, y);
        std::cout << " ";
        std::cout << std::endl;
    }
    //Movemos el cursor a ++y para imprimir la ultima linea del marco.
    MoverCursor(x, ++y);
    for (int n = -1; n <= w; n++) std::cout << " ";

}

int * CrearArreglo(int dim) {
    if (dim <= 0) throw "Dimensio\242n incorrecta";
    int * ary = new int[dim];
    for (int i = 0; i < dim; i++) ary[i] = 0;
    return ary;
}

void DestruirArreglo(int * & ary) {
    delete[] ary;
    ary = NULL;
}

void swp(int * ary, int x, int y) {
    int aux = ary[x];
    ary[x] = ary[y];
    ary[y] = aux;
}

void set_cursor(bool visible) {
    Console::instance().set_cursor_visible(visible);
}

