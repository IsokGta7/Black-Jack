#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <time.h>
#include <windows.h>

#include "Utileria.h"
#include "Cartas.h"
#include "Titulos.h"
#include "ColorConsola.h"
#include "Titulos.h"

void Jugar() {
    //Posición del cursor para jugar de nuevo.
    int posf = AGAIN;
    Baraja baraja;
    LlenarBaraja(baraja);
    do {
        system("cls");
        ImprimirTitulo((220 - 181) / 2, 0);
        int sumaD = 0, sumaJ = 0, x = 4, pos = PEDIR, cartasD = 0, cartasJ = 0, pull = 0, o = PEDIR;
        bool finished = false;
        Shuffle(baraja);
        //El maximo de cartas que ambos pueden tener es 5.
        int * barajaJ = CrearArreglo(5);
        int * barajaD = CrearArreglo(5);
        //Impresión de la interfaz
        MoverCursor(5, 55);
        std::cout << green << "Pedir";
        MoverCursor(18, 55);
        std::cout << "Plantar";
        MoverCursor(4, 12);
        std::cout << red << "Dealer:" << std::endl;
        //Imprime la carta volteada del dealer
        ImprimirCartaVolteada(x + 17, 13, 15, 13);
        //Cada vez que se "tome" una carta aumentamos el valor de pull para llevar la cuenta de que tarjeta se tiene que tomar.
        ImprimirCarta(x, 13, 13, 13, pull, baraja);
        barajaD[0] = pull;
        cartasD++;
        pull++;

        MoverCursor(4, 29);
        std::cout << green << "Jugador: " << std::endl;
        //El jugador comienza con dos cartas las cuales se sacan aquí.
        for (int j = 0; j <= 1; j++) {
            ImprimirCarta(x, 30, 13, 13, pull, baraja);
            barajaJ[j] = pull;
            cartasJ++;
            pull++;
            x += 17;
        }
        //Calculamos ambas sumas para poder imprimirlas.
        sumaJ = CalcularSuma(barajaJ, cartasJ, baraja);
        sumaD = CalcularSuma(barajaD, cartasD, baraja);

        MoverCursor(4, 49);
        std::cout << red << "Puntuaci\xA2n Dealer: " << sumaD;
        MoverCursor(4, 50);
        std::cout << green << "Puntuaci\xA2n Jugador: " << sumaJ;

        DibujarMarco(7, 2, 3, 54);
        //Si el jugador obtiene una carta de valor 10 y un as puede ganar por lo que confirmarmos si ha ganado o no.
        if (sumaJ == 21) {
            posf = Resultados(GANO);
            finished = true;
        }

        //Si el jugador no ha terminado su mano se repite la acción de pedir una carta o plantar su mano.
        while (finished == false) {
            o = PEDIR;
            while (o != ENTER) {
                o = getch();
                switch (o) {
                case RIGHT:
                    if (pos == PLANTAR) break;
                    else {
                        pos = PLANTAR;
                        DibujarMarco(7, 2, 17, 54);
                        BorrarMarco(7, 2, 3, 54);
                        break;
                    }
                    case LEFT:
                        if (pos == PEDIR) break;
                        else {
                            pos = PEDIR;
                            DibujarMarco(7, 2, 3, 54);
                            BorrarMarco(7, 2, 17, 54);
                            break;
                        }
                }
            }
            //Al presionar enter se va a romper el ciclo, si pide una carta sumamos una carta más y calculamos la puntuación, de lo contrario se realiza el juego del Dealer.
            if (pos == PEDIR) {
                ImprimirCarta(x, 30, 13, 13, pull, baraja);
                barajaJ[cartasJ] = pull;
                pull++;
                x += 17;
                cartasJ++;
                sumaJ = CalcularSuma(barajaJ, cartasJ, baraja);
                MoverCursor(4, 50);
                std::cout << green << "Puntuaci\xA2n Jugador: " << sumaJ;
                //Revisamos todas las condiciones para los resultados
                if (sumaJ > 21) {
                    posf = Resultados(PERDIO);
                    finished = true;
                } else if ((sumaJ == 21) || (cartasJ == 5 && sumaJ < 21)) {
                    posf = Resultados(GANO);
                    finished = true;
                }
            } else {
                sumaD = JuegoDealer(barajaD, cartasD, baraja, pull);
                if (sumaD > 21 || sumaJ > sumaD) {
                    posf = Resultados(GANO);
                } else if (sumaD > sumaJ) {
                    posf = Resultados(PERDIO);
                } else {
                    posf = Resultados(EMPATE);
                }
                finished = true;
            }
        }
        DestruirArreglo(barajaJ);
        DestruirArreglo(barajaD);
    } while (posf != SALIRJ); //Este while permite que el jugador pueda elegir jugar de nuevo en la pantalla de resultados.
}

//***************************************************************************************************************************************************************************************************************************************
int JuegoDealer(int * & barajaD, int ncartas, Baraja & baraja, int pull) {
    int x = 21, y = 1, i = 0;
    int suma = CalcularSuma(barajaD, ncartas, baraja);
    while (i <= 5) {
        //El Dealer solo puede tomar cartas si su puntuación es menor o igual a 16 de lo contrario se tiene que plantar (limitado a 5 cartas).
        if (suma <= 16) {
            ImprimirCarta(x, 13, 13, 13, pull, baraja);
            barajaD[y] = pull;
            ncartas++;
            y++;
            pull++;
            x += 17;
            suma = CalcularSuma(barajaD, ncartas, baraja);
            MoverCursor(4, 49);
            std::cout << red << "Puntuaci\xA2n Dealer: " << suma;
        } else {
            MoverCursor(4, 49);
            std::cout << red << "Puntuaci\xA2n Dealer: " << suma;
            return suma;
        }
        i++;
        sleep(1);
    }
    return suma;
}

//***************************************************************************************************************************************************************************************************************************************
int Resultados(int r) {
    int o = 0, pos;
    //Se imprimen los marcos de la pantalla de resultados.

    std::cout << white;

    DibujarMarcoSolido(120, 20, (220 - 120) / 2, (60 - 20) / 2);

    DibujarMarco(120, 21, (220 - 120) / 2, (60 - 21) / 2);

    //Dependiendo del resultado imprimimos un titulo.
    switch (r) {
    case PERDIO:
        ImprimirPerder(1 + ((220 - 120) + (120 - 107)) / 2, (60 - 20) / 2 + 1);
        break;
    case GANO:
        ImprimirGanar(1 + ((220 - 120) + (120 - 92)) / 2, (60 - 20) / 2 + 1);
        break;
    case EMPATE:
        ImprimirEmpate(1 + ((220 - 120) + (120 - 63)) / 2, (60 - 20) / 2 + 1);
        break;
    }
    //Se pregunta si se desea jugar de nuevo o no.
    MoverCursor(((60 - 11) + (220 - 120)) / 2, 36);
    std::cout << yellow << "Volver a jugar" << std::endl;
    MoverCursor(30 + ((220 - 120) + (120 - 5)) / 2, 36);
    std::cout << "Regresar" << red << std::endl;
    DibujarMarco(16, 2, -2 + ((60 - 11) + (220 - 120)) / 2, 34);
    while (o != ENTER) {
        o = getch();
        switch (o) {
        case RIGHT:
            if (pos == SALIRJ) break;
            else {
                pos = SALIRJ;
                BorrarMarco(16, 2, -2 + ((60 - 11) + (220 - 120)) / 2, 34);
                DibujarMarco(16, 2, 24 + ((220 - 120) + (120 - 5)) / 2, 34);
                break;
            }
            case LEFT:
                if (pos == AGAIN) break;
                else {
                    pos = AGAIN;
                    BorrarMarco(16, 2, 24 + ((220 - 120) + (120 - 5)) / 2, 34);
                    DibujarMarco(16, 2, -2 + ((60 - 11) + (220 - 120)) / 2, 34);
                    break;
                }
                default:
                    break;
        }
    }
    //   EstablecerColor(NEGRO,BLANCO);
    return pos;
}

//***************************************************************************************************************************************************************************************************************************************
int CalcularSuma(int * & cartas, int ncartas, Baraja & baraja) {
    int suma = 0, nas = 0;
    bool ace = false;
    //Recorremos toda la baraja y contamos el numero de aces que hay mientras sumaoms la puntuación.
    for (int i = 0; i < ncartas; i++) {
        if (baraja.cartas[cartas[i]].numero == 1) {
            suma += 11;
            ace = true;
            nas++;
        } else if (baraja.cartas[cartas[i]].numero == 11 || baraja.cartas[cartas[i]].numero == 12 || baraja.cartas[cartas[i]].numero == 13)
            suma += 10;
        else suma += baraja.cartas[cartas[i]].numero;
    }
    //Si la suma es mayor a 21 y hay un as vamos reduciendo el valor del as a 1 (restandole 10 porque le quitaría 11 del as y le sumaría 1 del nuevo valor -11+1=-10).
    if (suma > 21 && ace == true) {
        for (int i = 0; i < nas; i++) {
            if (suma > 21) {
                suma -= 10;
            }
        }
    }
    return suma;
}

//***************************************************************************************************************************************************************************************************************************************
void ImprimirCarta(int x, int y, int w, int h, int carta, Baraja & baraja) {
    //Determina el simbolo de la carta
    std::string simbolocarta = DeterminarSimbolo(carta, baraja);
    std::string numerocarta = DeterminarRango(carta, baraja);
    int numero;
    // Para imprimir el patrón del centro de la carta es necesario tener el valor numerico en numero (y no en string) por lo que lo determinamos aquí.
    if (numerocarta == "A" || numerocarta == "J" || numerocarta == "K" || numerocarta == "A" || numerocarta == "Q") numero = 1;
    else numero = std::stoi(numerocarta);
    std::cout << white;
    //Impresión del marco de la carta
    DibujarMarcoSolido(w + 2, h, x, y);
    //Impresión de las gifuras de la esquina.
    ImprimirEsquinas(carta, x, y, w + 2, h, baraja, simbolocarta, numerocarta);
    //Impresión del patron del centro.
    ImprimirCentro(x, y, w + 2, h, simbolocarta, numero);
    //Devolvemos el output al original.
    SetConsoleOutputCP(850);
}

//***************************************************************************************************************************************************************************************************************************************
void ImprimirCentro(int x, int y, int w, int h, std::string simbolocarta, int rango) {

    switch (rango) {
    case 2:
        for (int i = 0; i <= 2; i += 2) {
            MoverCursor(x + 1 + w / 2, y + i + h / 2);
            std::cout << simbolocarta;
        }
        break;
    case 3:
        for (int i = -1; i <= 4; i += 2) {
            MoverCursor(x + 1 + w / 2, y + i + h / 2);
            std::cout << simbolocarta;
        }
        break;
    case 4:
        for (int i = 1; i <= 2; i++) {
            for (int k = 1; k <= 2; k++) {
                MoverCursor(x + 1 + i * (w / 3), y + 1 + k * (h / 3));
                std::cout << simbolocarta;
            }
        }
        break;
    case 5:
        for (int i = 1; i <= 2; i++) {
            for (int k = 1; k <= 2; k++) {
                MoverCursor(x + 1 + i * (w / 3), y + 1 + k * (h / 3));
                std::cout << simbolocarta;
            }
        }
        MoverCursor(x + 1 + w / 2, y + 1 + h / 2);
        std::cout << simbolocarta;
        break;
    case 6:
        for (int i = 1; i <= 2; i++) {
            for (int k = 1; k <= 3; k++) {
                MoverCursor(x + 1 + i * (w / 3), y - 1 + k * (h / 3));
                std::cout << simbolocarta;
            }
        }
        break;
    case 7:
        for (int i = 1; i <= 2; i++) {
            for (int k = 1; k <= 3; k++) {
                MoverCursor(x + 1 + i * (w / 3), y - 1 + k * (h / 3));
                std::cout << simbolocarta;
            }
        }
        MoverCursor(x + 1 + w / 2, y + 1 + h / 2);
        std::cout << simbolocarta;
        MoverCursor(20, 20);
        break;
    case 8:
        for (int i = 1; i <= 2; i++) {
            for (int k = 1; k <= 4; k++) {
                MoverCursor(x + 1 + i * (w / 3), y - 3 + k * (h / 3));
                std::cout << simbolocarta;
            }
        }
        break;
    case 9:
        for (int i = 1; i <= 2; i++) {
            for (int k = 1; k <= 4; k++) {
                MoverCursor(x + 1 + i * (w / 3), y - 3 + k * (h / 3));
                std::cout << simbolocarta;
            }
        }
        MoverCursor(x + 1 + w / 2, y + 1 + h / 2);
        std::cout << simbolocarta;
        MoverCursor(20, 20);
        break;
    case 10:
        for (int m = 0; m <= h / 2; m += h / 2) {
            for (int i = 1; i <= 2; i++) {
                for (int k = 1; k <= 2; k++) {
                    MoverCursor(x + 1 + i * (w / 3), m + y + 1 + k * (h / 6));
                    std::cout << simbolocarta;
                }
            }
            MoverCursor(x + 1 + w / 2, m + y + 1 + h / 4);
            std::cout << simbolocarta;
        }
        break;
    default:
        MoverCursor(x + 1 + w / 2, y + 1 + h / 2);
        std::cout << simbolocarta;

    }
}

//***************************************************************************************************************************************************************************************************************************************
void Instrucciones() {
    system("cls");
    ImprimirTitulo((220 - 181) / 2, 0);
    int o = 0;
    ImprimirReglas((220 - 45) / 2, 12);
    MoverCursor((220 - 75) / 2, 21);
    std::cout << blue << char(254) << " El Dealer repartir\xA0 dos cartas descubiertas al jugador y una descubierta a s\xA1 mismo.";
    MoverCursor((220 - 78) / 2, 23);
    std::cout << blue << char(254) << " El jugador decide si pide m\xA0s cartas o se planta con las dos que ya recibi\xA2";
    MoverCursor((220 - 117) / 2, 25);
    std::cout << blue << char(254) << " Al pedir una carta su valor se suma a la puntuaci\xA2n del jugador. Al plantarse, el jugador no podr\xA0 pedir m\xA0s cartas.";
    MoverCursor((220 - 139) / 2, 27);
    std::cout << char(254) << " Las cartas del 2 al 10 valen su valor num\x82rico; las cartas J, Q y K valen 10 y el as vale 1 o 11 seg\xA3n la conveniencia del jugador.";
    MoverCursor((220 - 192) / 2, 29);
    std::cout << char(254) << " Una vez terminada la mano del jugador el Dealer jugar\xA0 la suya. Los jugadores que se queden m\xA0s lejos de 21 que el Dealer o que hayan sobrepasado este valor, pierden.";
    MoverCursor((220 - 164) / 2, 31);
    std::cout << char(254) << " El Dealer no tiene la posibilidad de tomar alguna decisi\xA2n sobre el juego. Si su puntuaci\xA2n es de 16 o menos tiene que pedir, si suma 17 o m\xA0s tiene que plantarse.";
    MoverCursor((220 - 128) / 2, 33);
    std::cout << char(254) << " Los jugadores que tengan 21 o esten m\xA0s cerca de 21 que el Dealer, ganan. Adem\xA0s, si el Dealer sobrepasa el 21, el jugador gana.";
    MoverCursor((220 - 77) / 2, 35);
    std::cout << char(254) << " Si el jugador toma 5 cartas y no sobrepasa o alcanza el 21, el jugador gana.";
    MoverCursor((220 - 61) / 2, 37);
    std::cout << char(254) << " Si ambos tienen el mismo valor el juego termina en un empate.";
    ImprimirControles((220 - 64) / 2, 39);
    MoverCursor((220 - 81) / 2, 47);
    std::cout << blue << char(254) << " Para movimiento entre opciones se utilizan las flechas direccionales del teclado.";
    MoverCursor((220 - 145) / 2, 49);
    std::cout << char(254) << " Para acceder a alguna opci\xA2n se utiliza la tecla <ENTER>. Algunas de las opciones son 'Pedir', 'Plantar', 'OK' y las opciones del men\xA3 principal." << red;
    DibujarMarco(7, 2, -3 + (220 - 2) / 2, 53);
    MoverCursor((220 - 2) / 2, 54);
    std::cout << green << "OK." << std::endl;
    while (true) {
        o = getch();
        if (o == ENTER) break;
    }

}
//***************************************************************************************************************************************************************************************************************************************
void Creditos() {
    system("cls");
    int o = 0;
    system("cls");
    ImprimirTitulo((220 - 181) / 2, 0);
    ImprimirCreditos((220 - 55) / 2, 12);
    MoverCursor((220 - 166) / 2, 24);
    std::cout << blue << "Este programa fue hecho como proyecto final de la clase de Programaci\xA2n de Computadoras de la Universidad de Sonora a cargo de la maestra Irene Rodriguez Castillo";
    ImprimirAutores((220 - 52) / 2, 28);
    MoverCursor((220 - 28) / 2, 39);
    std::cout << blue << char(254) << " Carlos Eduardo Gonzalez Ruiz";
    MoverCursor((220 - 25) / 2, 41);
    std::cout << blue << char(254) << " Luis Mario Sainz Pe\xA4u\xA4uri";
    MoverCursor((220 - 30) / 2, 43);
    std::cout << blue << char(254) << " Ezequiel Isaac Rodriguez Tenorio" << red;
    DibujarMarco(7, 2, -3 + (220 - 2) / 2, 47);
    MoverCursor((220 - 2) / 2, 48);
    std::cout << green << "OK." << std::endl;
    while (true) {
        o = getch();
        if (o == ENTER) break;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void LlenarBaraja(Baraja & baraja) {
    int j = 0;
    //Hay 4 palos con 13 cartas cada uno, un for que va de 0 a 3 para los palos y un for que va de 1 a 13 para las cartas de cada palo.
    for (int k = 0; k < 4; k++) {
        for (int i = 1; i <= 13; i++) {
            baraja.cartas[j].palo = k;
            baraja.cartas[j].numero = i;
            j++;
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void Shuffle(Baraja & baraja) {
    //Ya que es una estructura no se tiene que procesar elemento por elemento.
    int x, y, paloaux, numeroaux;
    int i = rand() % 500 + 300;
    //Para minimizar las posibilidades de que la baraja no quede muy revuelta se repiten los intercambios de 300 a 500 veces.
    for (int j = 0; j < i; j++) {
        x = rand() % 52;
        y = rand() % 52;
        paloaux = baraja.cartas[x].palo;
        numeroaux = baraja.cartas[x].numero;
        baraja.cartas[x].palo = baraja.cartas[y].palo;
        baraja.cartas[x].numero = baraja.cartas[y].numero;
        baraja.cartas[y].palo = paloaux;
        baraja.cartas[y].numero = numeroaux;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void ImprimirEsquinas(int carta, int x, int y, int w, int h, Baraja & baraja, std::string simbolocarta, std::string numerocarta) {
    DeterminarColor(carta, baraja);
    // Es necesario cambiar el output a UTF8 para poder imprimir las figuras sin tener que cambiar la fuente desde la consola.
    SetConsoleOutputCP(CP_UTF8);
    MoverCursor(x + 1, y + 1);
    std::cout << numerocarta;
    MoverCursor(x + 1, y + 2);
    std::cout << simbolocarta;
    MoverCursor(x + w, h + y);
    if (numerocarta == "10") std::cout << '\b';
    std::cout << numerocarta;
    MoverCursor(x + w, h + y - 1);
    std::cout << simbolocarta;

}
//***************************************************************************************************************************************************************************************************************************************
std::string DeterminarSimbolo(int carta, Baraja & baraja) {
    switch (baraja.cartas[carta].palo) {
    case CORAZON:
        return "♥";
    case DIAMANTE:
        return "♦";
    case TREBOL:
        return "♣";
    case ESPADA:
        return "♠";
    }
    std::cerr << "Palo inválido al determinar símbolo: " << baraja.cartas[carta].palo << std::endl;
    return "";
}
//***************************************************************************************************************************************************************************************************************************************
void DeterminarColor(int carta, Baraja & baraja) {
    if (baraja.cartas[carta].palo == DIAMANTE || baraja.cartas[carta].palo == CORAZON) {
        std::cout << red;
    } else {
        std::cout << green;
    }
}
//***************************************************************************************************************************************************************************************************************************************
std::string DeterminarRango(int carta, Baraja & baraja) {
    switch (baraja.cartas[carta].numero) {

    case 1:
        return "A";
    case 11:
        return "J";
    case 12:
        return "Q";
    case 13:
        return "K";
    default:
        return std::to_string(baraja.cartas[carta].numero);
    }
}

//***************************************************************************************************************************************************************************************************************************************
void ImprimirCartaVolteada(int x, int y, int w, int h) {

    MoverCursor(x, y);
    std::cout << white << (char) ESI;
    for (int n = 0; n < w; n++) std::cout << (char) BH;
    std::cout << (char) ESD << std::endl;
    //Impresión del resto del marco menos la ultima linea
    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << (char) BV;
        for (int m = 0; m < w; m++) std::cout << (char) CV;
        std::cout << (char) BV;
    }
    //Movemos el cursor a ++y para imprimir la ultima linea del marco.
    MoverCursor(x, ++y);
    std::cout << (char) EII;
    for (int n = 0; n < w; n++) std::cout << (char) BH;
    std::cout << (char) EID << std::endl;
}
