#include <iostream>

#include "Menu.h"
#include "ColorConsola.h"
#include "Titulos.h"
#include "Utileria.h"
#include "GameLogic.h"

int Menu() {
    int y = 19, o, opcion = JUGAR;
    auto imprimirModo = []() {
        const GameMode &modo = ObtenerModoActual();
        MoverCursor(4, 60);
        std::cout << yellow << "Modo actual: " << modo.nombre;
        MoverCursor(4, 61);
        std::cout << yellow << FormatearModoResumen(modo) << " (\xE2\x86\x90/\xE2\x86\x92 para cambiar)";
    };
    //Se cambia el tamaño de la consola para que todo quede centrado y que los titulos quepan.
    CambiarTamanio(1800, 1000);
    //Impresión de todas las opciones del menú principal.
    MoverCursor(10, 5);
    ImprimirTitulo((220 - 181) / 2, 5);
    ImprimirJugar((220 - 37) / 2, 20);
    ImprimirInstrucciones(1 + (220 - 87) / 2, 28);
    ImprimirCreditos(1 + (220 - 55) / 2, 35);
    ImprimirSalir(1 + (220 - 36) / 2, 44);
    imprimirModo();
    //Se dibuja el marco de selección alrededor de la primera opción
    DibujarMarco(90, 7, -1 + (220 - 87) / 2, y);
    do {
        o = LeerTecla();
        if (o == LEFT) {
            CambiarModo(-1);
            imprimirModo();
            continue;
        }
        if (o == RIGHT) {
            CambiarModo(1);
            imprimirModo();
            continue;
        }
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
