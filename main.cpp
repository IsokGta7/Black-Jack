#include <iostream>
#include <time.h>

#include "Menu.h"
#include "Utileria.h"
#include "Cartas.h"
#include "Console.h"

using namespace std;

int main() {
    //Escondemos el cursor para que no flashee en la pantalla principal.
    set_cursor(false);
    //Cambiamos el titulo de la consola.
    Console::instance().set_title("BlackJack");
    //El seed para revolver la baraja.
    srand(time(NULL));
    while (true) {
        system("cls");
        //El menu devolver la opcion que eligio el usuario.
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
