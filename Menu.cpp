#include <iostream>
#include <conio.h>

#include "Menu.h"
#include "Titulos.h"
#include "Utileria.h"
#include "GameLogic.h"

int Menu() {
    int y = 19, o, opcion = JUGAR;
    //Se cambia el tamao de la consola para que todo quede centrado y que los titulos quepan.
    CambiarTamanio(1800, 1000);
    //Impresin de todas las opciones del men principal.
    MoverCursor(10, 5);
    ImprimirTitulo((220 - 181) / 2, 5);
    ImprimirJugar((220 - 37) / 2, 20);
    ImprimirInstrucciones(1 + (220 - 87) / 2, 28);
    ImprimirCreditos(1 + (220 - 55) / 2, 35);
    ImprimirSalir(1 + (220 - 36) / 2, 44);
    //Se dibuja el marco de seleccin alrededor de la primera opcin
    DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
    do {
        o = getch();
        if (o == ENTER) return opcion;

        int nuevaOpcion = ActualizarOpcionMenu(opcion, o);
        if (nuevaOpcion != opcion) {
            BorrarMarco(90, 7, -1 + (220 - 87) / 2, y);
            opcion = nuevaOpcion;
            y = 19 + (opcion - 1) * 8;
            DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
        }
    } while (true);
}
