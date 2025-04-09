#include <windows.h>
#include <iostream>

#include "Utileria.h"
#include "ColorConsola.h"

//***************************************************************************************************************************************************************************************************************************************
void MoverCursor(short x, short y) {
    COORD coord = {
        x,
        y
    };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    set_cursor(false);
}

//***************************************************************************************************************************************************************************************************************************************
void CambiarTamanio(int w, int h) {

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, & r);

    MoveWindow(console, r.left, r.top, w, h, TRUE);

}

//***************************************************************************************************************************************************************************************************************************************
void DibujarMarco(int w, int h, int x, int y) {

    MoverCursor(x, y);
    std::cout << (char) ESI;
    for (int n = 0; n < w; n++) std::cout << (char) BH;
    std::cout << (char) ESD << std::endl;
    //Impresión del resto del marco menos la ultima linea
    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << (char) BV;
        MoverCursor(x + w + 1, y);
        std::cout << (char) BV;
    }
    //Movemos el cursor a ++y para imprimir la ultima linea del marco.
    MoverCursor(x, ++y);
    std::cout << (char) EII;
    for (int n = 0; n < w; n++) std::cout << (char) BH;
    std::cout << (char) EID << std::endl;
}

//***************************************************************************************************************************************************************************************************************************************
void DibujarMarcoSolido(int w, int h, int x, int y) {

    MoverCursor(x, y);
    std::cout << (char) ESI;
    for (int n = 0; n < w; n++) std::cout << (char) BH;
    std::cout << (char) ESD << std::endl;
    //Impresión del resto del marco menos la ultima linea
    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << (char) BV;
        for (int m = 0; m < w; m++) std::cout << " ";
        std::cout << (char) BV;
    }
    //Movemos el cursor a ++y para imprimir la ultima linea del marco.
    MoverCursor(x, ++y);
    std::cout << (char) EII;
    for (int n = 0; n < w; n++) std::cout << (char) BH;
    std::cout << (char) EID << std::endl;
}

//***************************************************************************************************************************************************************************************************************************************
void BorrarMarco(int w, int h, int x, int y) {
    MoverCursor(x, y);
    for (int n = -1; n <= w; n++) std::cout << " ";
    //Impresión del resto del marco menos la ultima linea
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

//***************************************************************************************************************************************************************************************************************************************
int * CrearArreglo(int dim) {
    if (dim <= 0) throw "Dimensi\242n incorrecta";
    int * ary = new int[dim];
    for (int i = 0; i < dim; i++) ary[i] = 0;
    return ary;
}

//***************************************************************************************************************************************************************************************************************************************
void DestruirArreglo(int * & ary) {
    delete[] ary;
    ary = NULL;
}

//***************************************************************************************************************************************************************************************************************************************
void swp(int * ary, int x, int y) {
    int aux = ary[x];
    ary[x] = ary[y];
    ary[y] = aux;
}

//***************************************************************************************************************************************************************************************************************************************
void set_cursor(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & info);
}
