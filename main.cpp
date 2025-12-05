#include <iostream>
#include <time.h>

#include "Menu.h"
#include "Utileria.h"
#include "Cartas.h"
#include "Console.h"

using namespace std;

int main() {
    // Configurar la consola para usar UTF-8 y minimizar problemas de glifos.
    ConfigurarCodificacion();
    //Escondemos el cursor para que no flashee en la pantalla principal.
    set_cursor(false);
    //Cambiamos el titulo de la consola.
    ActualizarTitulo("BlackJack");
    //El seed para revolver la baraja.
    srand(time(NULL));
    while (true) {
        LimpiarPantalla();
        //El menu devolver la opcion que eligi el usuario.
        int option = Menu();
        switch (option) {
        case JUGAR:
            Jugar();
            break;
        case INSTRUCCIONES:
            Instrucciones();
            break;
        case CREDITOS:
            Creditos();
            break;
        case SALIR:
            return 0;
        }
    }
}
