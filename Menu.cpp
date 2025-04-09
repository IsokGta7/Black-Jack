#include <iostream>
#include <conio.h>

#include "Menu.h"
#include "Titulos.h"
#include "Utileria.h"

int Menu() {
    int y = 19, o, opcion = JUGAR;
    //Se cambia el tamaño de la consola para que todo quede centrado y que los titulos quepan.
    CambiarTamanio(1800, 1000);
    //Impresión de todas las opciones del menú principal.
    MoverCursor(10, 5);
    ImprimirTitulo((220 - 181) / 2, 5);
    ImprimirJugar((220 - 37) / 2, 20);
    ImprimirInstrucciones(1 + (220 - 87) / 2, 28);
    ImprimirCreditos(1 + (220 - 55) / 2, 35);
    ImprimirSalir(1 + (220 - 36) / 2, 44);
    //Se dibuja el marco de selección alrededor de la primera opción
    DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
    do {
        o = getch();
        switch (o) {
        case UP:
            //Si se presiona la flecha hacia arriba cuando se esta en la primera opción el marco se mueve hacia la última de lo contrario se mueve una posición hacia arriba (las posiciones tienen 8 de diferencia en y)
            if (opcion == JUGAR) {
                opcion = SALIR;
                BorrarMarco(90, 7, -1 + (220 - 87) / 2, y);
                y = 43;
                DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
            } else {
                opcion -= 1;
                BorrarMarco(90, 7, -1 + (220 - 87) / 2, y);
                y -= 8;
                DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
            }
            break;
        case DOWN:
            //Si se presiona la flecha hacia abajo cuando se esta en la última opción el marco se mueve hacia la primera de lo contrario se mueve una posición hacia abajo (las posiciones tienen 8 de diferencia en y)
            if (opcion == SALIR) {
                opcion = JUGAR;
                BorrarMarco(90, 7, -1 + (220 - 87) / 2, y);
                y = 19;
                DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
            } else {
                opcion += 1;
                BorrarMarco(90, 7, -1 + (220 - 87) / 2, y);
                y += 8;
                DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
            }
            break;
        case ENTER:
            //Termina la ejecución de la función y devuelve la posición (la opción en la que presionó enter) para que el main decida que imprimir.
            return opcion;
        }
    } while (true);
}
