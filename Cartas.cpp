#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <vector>

#include "Utileria.h"
#include "Cartas.h"
#include "Titulos.h"
#include "ColorConsola.h"
#include "GameLogic.h"

namespace {

int ClampToScreen(int value, int limit, int span = 1) {
    if (limit <= 0) return 0;
    if (span >= limit) return 0;
    if (value < 0) return 0;
    if (value + span > limit) return limit - span;
    return value;
}

ElementoLayout CrearElemento(int x, int y, int width, int height, const TerminalSize &tamano) {
    int finalWidth = std::min(width, std::max(1, tamano.width));
    int finalHeight = std::min(height, std::max(1, tamano.height));
    return {ClampToScreen(x, tamano.width, finalWidth), ClampToScreen(y, tamano.height, finalHeight), finalWidth, finalHeight};
}

void DibujarMarcoCartaDecorado(int w, int h, int x, int y) {
    MoverCursor(x, y);
    std::cout << BOX_DOUBLE_TOP_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_DOUBLE_HORIZONTAL;
    std::cout << BOX_DOUBLE_TOP_RIGHT << std::endl;

    for (int n = 0; n < h; n++) {
        MoverCursor(x, y + n + 1);
        std::cout << BOX_DOUBLE_VERTICAL;
#ifndef _WIN32
        int color = 255 - (n % 4) * 5;
        std::cout << "\033[48;5;" << color << "m";
        for (int m = 0; m < w; m++) std::cout << " ";
        std::cout << RESET;
#else
        const char *relleno = (n % 2 == 0) ? u8"░" : " ";
        for (int m = 0; m < w; m++) std::cout << relleno;
#endif
        std::cout << BOX_DOUBLE_VERTICAL;
    }

    MoverCursor(x, y + h + 1);
    std::cout << BOX_DOUBLE_BOTTOM_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_DOUBLE_HORIZONTAL;
    std::cout << BOX_DOUBLE_BOTTOM_RIGHT << std::endl;
}

void IluminarCentroCarta(int x, int y, int w, int h) {
#ifndef _WIN32
    for (int fila = 2; fila < h; fila += 3) {
        MoverCursor(x + 1, y + fila);
        int color = 252 - (fila % 4);
        std::cout << "\033[48;5;" << color << "m";
        for (int col = 0; col < w; ++col) std::cout << " ";
        std::cout << RESET;
    }
#else
    for (int fila = 2; fila < h; fila += 3) {
        MoverCursor(x + 1, y + fila);
        const char *relleno = (fila % 2 == 0) ? u8"·" : " ";
        for (int col = 0; col < w; ++col) std::cout << relleno;
    }
#endif
}

}

JuegoLayout CalcularLayoutJuego(const TerminalSize &tamano) {
    const int tituloWidth = 181;
    JuegoLayout layout{};
    layout.titulo = CrearElemento(CentrarEnDimension(tamano.width, tituloWidth), 0, tituloWidth, 1, tamano);
    return layout;
}

InstruccionesLayout CalcularLayoutInstrucciones(const TerminalSize &tamano) {
    InstruccionesLayout layout{};
    layout.titulo = CrearElemento(CentrarEnDimension(tamano.width, 181), 0, 181, 1, tamano);
    layout.reglas = CrearElemento(CentrarEnDimension(tamano.width, 45), ClampToScreen(12, tamano.height), 45, 6, tamano);
    layout.okMarco = CrearElemento(CentrarEnDimension(tamano.width, 7) - 3, ClampToScreen(53, tamano.height), 7, 2, tamano);
    layout.okTexto = CrearElemento(CentrarEnDimension(tamano.width, 2), ClampToScreen(54, tamano.height), 2, 1, tamano);
    return layout;
}

ResultadosLayout CalcularLayoutResultados(const TerminalSize &tamano) {
    ResultadosLayout layout{};
    int anchoMarco = std::min(120, std::max(20, tamano.width - 2));
    int altoMarco = std::min(20, std::max(6, tamano.height - 2));
    int altoMarcoHueco = std::min(21, std::max(6, tamano.height - 1));
    layout.marcoSolido = CrearElemento(CentrarEnDimension(tamano.width, anchoMarco), CentrarEnDimension(tamano.height, altoMarco), anchoMarco, altoMarco, tamano);
    layout.marcoHueco = CrearElemento(layout.marcoSolido.x, CentrarEnDimension(tamano.height, altoMarcoHueco), anchoMarco, altoMarcoHueco, tamano);

    const int tituloY = ClampToScreen(layout.marcoSolido.y + 1, tamano.height);
    layout.tituloPerdio = CrearElemento(layout.marcoSolido.x + 1 + CentrarEnDimension(layout.marcoSolido.width, 107), tituloY, 107, 1, tamano);
    layout.tituloGano = CrearElemento(layout.marcoSolido.x + 1 + CentrarEnDimension(layout.marcoSolido.width, 92), tituloY, 92, 1, tamano);
    layout.tituloEmpate = CrearElemento(layout.marcoSolido.x + 1 + CentrarEnDimension(layout.marcoSolido.width, 63), tituloY, 63, 1, tamano);

    const int opcionesY = ClampToScreen(layout.marcoSolido.y + layout.marcoSolido.height - 4, tamano.height);
    const int anchoMarcoOpcion = 16;
    layout.volver = CrearElemento(layout.marcoSolido.x + CentrarEnDimension(layout.marcoSolido.width / 2, 14), opcionesY, 14, 1, tamano);
    layout.regresar = CrearElemento(layout.marcoSolido.x + layout.marcoSolido.width / 2 + CentrarEnDimension(layout.marcoSolido.width / 2, 8), opcionesY, 8, 1, tamano);
    layout.marcoVolver = CrearElemento(layout.volver.x - 2, opcionesY - 2, anchoMarcoOpcion, 2, tamano);
    layout.marcoRegresar = CrearElemento(layout.regresar.x - 2, opcionesY - 2, anchoMarcoOpcion, 2, tamano);
    return layout;
}

void Jugar() {
    //Posición del cursor para jugar de nuevo.
    int posf = AGAIN;
    //Barajas
    Baraja baraja;
    do {
        const GameMode &modo = ObtenerModoActual();
        int victorias = 0;
        int empates = 0;
        int derrotas = 0;
        int rondasTotales = std::max(1, modo.rondas);
        for (int ronda = 1; ronda <= rondasTotales; ++ronda) {
            LimpiarPantalla();
            TerminalSize tamano = ObtenerTamanoTerminal();
            JuegoLayout layout = CalcularLayoutJuego(tamano);
            ImprimirTitulo(layout.titulo.x, layout.titulo.y);
            MoverCursor(4, 9);
            std::cout << yellow << "Modo: " << modo.nombre;
            MoverCursor(4, 10);
            std::cout << yellow << FormatearModoResumen(modo);
            MoverCursor(4, 11);
            std::cout << yellow << "Ronda " << ronda << " de " << rondasTotales;

            int sumaD = 0, sumaJ = 0, x = 4, pos = PEDIR, cartasD = 0, cartasJ = 0, pull = 0, o = PEDIR;
            bool finished = false;
            LlenarBaraja(baraja);
            Shuffle(baraja);

            int *barajaJ = CrearArreglo(modo.maxCartasJugador);
            int *barajaD = CrearArreglo(modo.maxCartasDealer);
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
            for (int j = 0; j <= 1 && j < modo.maxCartasJugador; j++) {
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
            std::cout << red << "Puntuación Dealer: " << sumaD;
            MoverCursor(4, 50);
            std::cout << green << "Puntuación Jugador: " << sumaJ;

            DibujarMarco(7, 2, 3, 54);
            //Si el jugador obtiene una carta de valor 10 y un as puede ganar por lo que confirmarmos si ha ganado o no.
            if (sumaJ == modo.objetivo) {
                int resultado = AjustarResultadoPorModo(GANO, modo);
                if (resultado == GANO) victorias++;
                else empates++;
                finished = true;
            }

            //Si el jugador no ha terminado su mano se repite la acción de pedir una carta o plantar su mano.
            while (finished == false) {
                o = PEDIR;
                while (o != ENTER) {
                    o = LeerTecla();
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
                if (pos == PEDIR && cartasJ < modo.maxCartasJugador) {
                    ImprimirCarta(x, 30, 13, 13, pull, baraja);
                    barajaJ[cartasJ] = pull;
                    pull++;
                    x += 17;
                    cartasJ++;
                    sumaJ = CalcularSuma(barajaJ, cartasJ, baraja);
                    MoverCursor(4, 50);
                    std::cout << green << "Puntuación Jugador: " << sumaJ;
                    //Revisamos todas las condiciones para los resultados
                    if (sumaJ > modo.objetivo) {
                        int resultado = AjustarResultadoPorModo(PERDIO, modo);
                        if (resultado == EMPATE) empates++;
                        else derrotas++;
                        finished = true;
                    } else if ((sumaJ == modo.objetivo) || (cartasJ == modo.maxCartasJugador && sumaJ < modo.objetivo && modo.ganaPorMaxCartas)) {
                        int resultado = AjustarResultadoPorModo(GANO, modo);
                        if (resultado == GANO) victorias++;
                        else empates++;
                        finished = true;
                    }
                } else {
                    sumaD = JuegoDealer(barajaD, cartasD, baraja, pull, modo);
                    int resultado = DeterminarResultadoMano(sumaJ, sumaD, cartasJ, cartasD, modo);
                    if (resultado == GANO) victorias++;
                    else if (resultado == PERDIO) derrotas++;
                    else empates++;
                    finished = true;
                }

                if (cartasJ >= modo.maxCartasJugador && finished == false) {
                    sumaD = JuegoDealer(barajaD, cartasD, baraja, pull, modo);
                    int resultado = DeterminarResultadoMano(sumaJ, sumaD, cartasJ, cartasD, modo);
                    if (resultado == GANO) victorias++;
                    else if (resultado == PERDIO) derrotas++;
                    else empates++;
                    finished = true;
                }
            }

            DestruirArreglo(barajaJ);
            DestruirArreglo(barajaD);

            if (ronda < rondasTotales) {
                MoverCursor(4, 52);
                std::cout << yellow << "Ronda terminada. Marcador: " << victorias << "G-" << empates << "E-" << derrotas << "P";
                MoverCursor(4, 53);
                std::cout << yellow << "Presiona ENTER para la siguiente ronda.";
                while (LeerTecla() != ENTER) {
                }
            }
        }

        int resultadoFinal = EMPATE;
        if (victorias > derrotas) resultadoFinal = GANO;
        else if (derrotas > victorias) resultadoFinal = PERDIO;
        resultadoFinal = AjustarResultadoPorModo(resultadoFinal, modo);

        GameSummary resumen{modo, resultadoFinal, victorias, empates, derrotas, std::max(1, modo.rondas)};
        posf = Resultados(resumen);
    } while (posf != SALIRJ); //Este while permite que el jugador pueda elegir jugar de nuevo en la pantalla de resultados.
}
int JuegoDealer(int * & barajaD, int ncartas, Baraja & baraja, int pull, const GameMode &modo) {
    std::vector<int> mano(barajaD, barajaD + ncartas);
    DealerSimulationResult resultado = SimularJuegoDealer(mano, pull, baraja, modo);
    int x = 21;

    for (int carta : resultado.drawnCards) {
        ImprimirCarta(x, 13, 13, 13, carta, baraja);
        barajaD[ncartas] = carta;
        ncartas++;
        x += 17;
        int suma = CalcularSuma(barajaD, ncartas, baraja);
        MoverCursor(4, 49);
        std::cout << red << "Puntuación Dealer: " << suma;
        EsperarMilisegundos(1000);
    }

    MoverCursor(4, 49);
    std::cout << red << "Puntuación Dealer: " << resultado.total;

    return resultado.total;
}

//***************************************************************************************************************************************************************************************************************************************
int Resultados(const GameSummary &summary) {
    int o = 0, pos = AGAIN;
    //Se imprimen los marcos de la pantalla de resultados.

    std::cout << white;

    TerminalSize tamano = ObtenerTamanoTerminal();
    ResultadosLayout layout = CalcularLayoutResultados(tamano);

    DibujarMarcoSolido(layout.marcoSolido.width, layout.marcoSolido.height, layout.marcoSolido.x, layout.marcoSolido.y);

    DibujarMarco(layout.marcoHueco.width, layout.marcoHueco.height, layout.marcoHueco.x, layout.marcoHueco.y);

    //Dependiendo del resultado imprimimos un titulo.
    switch (summary.resultadoFinal) {
    case PERDIO:
        ImprimirPerder(layout.tituloPerdio.x, layout.tituloPerdio.y);
        break;
    case GANO:
        ImprimirGanar(layout.tituloGano.x, layout.tituloGano.y);
        break;
    case EMPATE:
        ImprimirEmpate(layout.tituloEmpate.x, layout.tituloEmpate.y);
        break;
    }

    int infoX = layout.marcoHueco.x + 4;
    int infoY = layout.marcoHueco.y + 3;
    MoverCursor(infoX, infoY);
    std::cout << yellow << "Modo: " << summary.modo.nombre;
    MoverCursor(infoX, infoY + 1);
    std::cout << yellow << FormatearModoResumen(summary.modo);
    MoverCursor(infoX, infoY + 2);
    std::cout << yellow << "Rondas jugadas: " << summary.rondasJugadas;
    MoverCursor(infoX, infoY + 3);
    std::cout << yellow << "Marcador G/E/P: " << summary.victorias << "/" << summary.empates << "/" << summary.derrotas;

    //Se pregunta si se desea jugar de nuevo o no.
    MoverCursor(layout.volver.x, layout.volver.y);
    std::cout << yellow << "Volver a jugar" << std::endl;
    MoverCursor(layout.regresar.x, layout.regresar.y);
    std::cout << "Regresar" << red << std::endl;
    DibujarMarco(layout.marcoVolver.width, layout.marcoVolver.height, layout.marcoVolver.x, layout.marcoVolver.y);
    while (o != ENTER) {
        o = LeerTecla();
        int nuevo = ActualizarOpcionResultados(pos, o);
        if (nuevo != pos) {
            if (nuevo == SALIRJ) {
                BorrarMarco(layout.marcoVolver.width, layout.marcoVolver.height, layout.marcoVolver.x, layout.marcoVolver.y);
                DibujarMarco(layout.marcoRegresar.width, layout.marcoRegresar.height, layout.marcoRegresar.x, layout.marcoRegresar.y);
            } else {
                BorrarMarco(layout.marcoRegresar.width, layout.marcoRegresar.height, layout.marcoRegresar.x, layout.marcoRegresar.y);
                DibujarMarco(layout.marcoVolver.width, layout.marcoVolver.height, layout.marcoVolver.x, layout.marcoVolver.y);
            }
            pos = nuevo;
        }
    }
    //   EstablecerColor(NEGRO,BLANCO);
    return pos;
}
//***************************************************************************************************************************************************************************************************************************************
//***************************************************************************************************************************************************************************************************************************************
void ImprimirCarta(int x, int y, int w, int h, int carta, Baraja & baraja) {
    //Determina el simbolo de la carta
    std::string simbolocarta = DeterminarSimbolo(carta, baraja);
    std::string numerocarta = DeterminarRango(carta, baraja);
    int numero;
    // Para imprimir el patrón del centro de la carta es necesario tener el valor numerico en numero (y no en string) por lo que lo determinamos aquí.
    if (numerocarta == "A" || numerocarta == "J" || numerocarta == "K" || numerocarta == "A" || numerocarta == "Q") numero = 1;
    else numero = std::stoi(numerocarta);
    const int anchoMarco = w + 2;
    AnimarAparicionRectangular(x, y, anchoMarco + 2, h + 2);
    std::cout << white;
    //Impresión del marco de la carta
    DibujarMarcoCartaDecorado(anchoMarco, h, x, y);
    //Impresión de las figuras de la esquina.
    ImprimirEsquinas(carta, x, y, anchoMarco, h, baraja, simbolocarta, numerocarta);
    //Impresión del patron del centro.
    ImprimirCentro(x, y, anchoMarco, h, simbolocarta, numero);
}

//***************************************************************************************************************************************************************************************************************************************
void ImprimirCentro(int x, int y, int w, int h, std::string simbolocarta, int rango) {
    IluminarCentroCarta(x, y, w, h);

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
    LimpiarPantalla();
    TerminalSize tamano = ObtenerTamanoTerminal();
    InstruccionesLayout layout = CalcularLayoutInstrucciones(tamano);
    ImprimirTitulo(layout.titulo.x, layout.titulo.y);
    int o = 0;
    ImprimirReglas(layout.reglas.x, layout.reglas.y);

    std::vector<std::string> lineas = {
        "El Dealer repartirá dos cartas descubiertas al jugador y una descubierta a sí mismo.",
        "El jugador decide si pide más cartas o se planta con las dos que ya recibió",
        "Al pedir una carta su valor se suma a la puntuación del jugador. Al plantarse, el jugador no podrá pedir más cartas.",
        "Las cartas del 2 al 10 valen su valor numérico; las cartas J, Q y K valen 10 y el as vale 1 o 11 según la conveniencia del jugador.",
        "Una vez terminada la mano del jugador el Dealer jugará la suya. Los jugadores que se queden más lejos de 21 que el Dealer o que hayan sobrepasado este valor, pierden.",
        "El Dealer no tiene la posibilidad de tomar alguna decisión sobre el juego. Si su puntuación es de 16 o menos tiene que pedir, si suma 17 o más tiene que plantarse.",
        "Los jugadores que tengan 21 o esten más cerca de 21 que el Dealer, ganan. Además, si el Dealer sobrepasa el 21, el jugador gana.",
        "Si el jugador toma 5 cartas y no sobrepasa o alcanza el 21, el jugador gana.",
        "Si ambos tienen el mismo valor el juego termina en un empate."
    };

    lineas.emplace_back("Si tu consola es lenta puedes desactivar las animaciones con BJ_ANIMATIONS=off o BJ_DISABLE_ANIMATIONS=1 antes de ejecutar el juego.");

    int y = ClampToScreen(layout.reglas.y + 9, tamano.height);
    for (const auto &linea : lineas) {
        int anchoLinea = static_cast<int>(linea.size()) + 2;
        int x = ClampToScreen(CentrarEnDimension(tamano.width, anchoLinea), tamano.width, anchoLinea);
        MoverCursor(x, y);
        std::cout << blue << char(254) << " " << linea;
        y = ClampToScreen(y + 2, tamano.height);
    }

    ImprimirControles(CentrarEnDimension(tamano.width, 64), ClampToScreen(y + 2, tamano.height));
    int ayudaY = ClampToScreen(y + 10, tamano.height);
    int ayudaY2 = ClampToScreen(ayudaY + 2, tamano.height);
    std::string controles = "Para movimiento entre opciones se utilizan las flechas direccionales del teclado.";
    std::string enter = "Para acceder a alguna opción se utiliza la tecla <ENTER>. Algunas de las opciones son 'Pedir', 'Plantar', 'OK' y las opciones del menú principal.";
    MoverCursor(CentrarEnDimension(tamano.width, static_cast<int>(controles.size()) + 2), ayudaY);
    std::cout << blue << char(254) << " " << controles;
    MoverCursor(CentrarEnDimension(tamano.width, static_cast<int>(enter.size()) + 2), ayudaY2);
    std::cout << char(254) << " " << enter << red;
    DibujarMarco(layout.okMarco.width, layout.okMarco.height, layout.okMarco.x, layout.okMarco.y);
    MoverCursor(layout.okTexto.x, layout.okTexto.y);
    std::cout << green << "OK." << std::endl;
    while (true) {
        o = LeerTecla();
        if (o == ENTER) break;
    }

}
//***************************************************************************************************************************************************************************************************************************************
void Creditos() {
    LimpiarPantalla();
    int o = 0;
    LimpiarPantalla();
    TerminalSize tamano = ObtenerTamanoTerminal();
    JuegoLayout layoutTitulo = CalcularLayoutJuego(tamano);
    ImprimirTitulo(layoutTitulo.titulo.x, layoutTitulo.titulo.y);
    ImprimirCreditos(CentrarEnDimension(tamano.width, 55), ClampToScreen(12, tamano.height));
    std::string texto = "Este programa fue hecho como proyecto final de la clase de Programación de Computadoras de la Universidad de Sonora a cargo de la maestra Irene Rodriguez Castillo";
    MoverCursor(CentrarEnDimension(tamano.width, static_cast<int>(texto.size())), ClampToScreen(24, tamano.height));
    std::cout << blue << texto;
    ImprimirAutores(CentrarEnDimension(tamano.width, 52), ClampToScreen(28, tamano.height));
    std::vector<std::string> autores = {
        "Carlos Eduardo Gonzalez Ruiz",
        "Luis Mario Sainz Peñuñuri",
        "Ezequiel Isaac Rodriguez Tenorio"
    };
    int autoresY = ClampToScreen(39, tamano.height);
    for (const auto &autor : autores) {
        int ancho = static_cast<int>(autor.size()) + 2;
        int x = ClampToScreen(CentrarEnDimension(tamano.width, ancho), tamano.width, ancho);
        MoverCursor(x, autoresY);
        std::cout << blue << char(254) << " " << autor;
        autoresY = ClampToScreen(autoresY + 2, tamano.height);
    }
    ElementoLayout okMarco = CrearElemento(CentrarEnDimension(tamano.width, 7) - 3, ClampToScreen(47, tamano.height), 7, 2, tamano);
    ElementoLayout okTexto = CrearElemento(CentrarEnDimension(tamano.width, 2), ClampToScreen(48, tamano.height), 2, 1, tamano);
    DibujarMarco(okMarco.width, okMarco.height, okMarco.x, okMarco.y);
    MoverCursor(okTexto.x, okTexto.y);
    std::cout << green << "OK." << std::endl;
    while (true) {
        o = LeerTecla();
        if (o == ENTER) break;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void ImprimirEsquinas(int carta, int x, int y, int w, int h, Baraja & baraja, std::string simbolocarta, std::string numerocarta) {
    DeterminarColor(carta, baraja);
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
    std::cout << white << BOX_TOP_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_HORIZONTAL;
    std::cout << BOX_TOP_RIGHT << std::endl;
    //Impresión del resto del marco menos la ultima linea
    for (int n = 0; n < h; n++) {
        MoverCursor(x, ++y);
        std::cout << BOX_VERTICAL;
        for (int m = 0; m < w; m++) std::cout << CARD_BACK_FILL;
        std::cout << BOX_VERTICAL;
    }
    //Movemos el cursor a ++y para imprimir la ultima linea del marco.
    MoverCursor(x, ++y);
    std::cout << BOX_BOTTOM_LEFT;
    for (int n = 0; n < w; n++) std::cout << BOX_HORIZONTAL;
    std::cout << BOX_BOTTOM_RIGHT << std::endl;
}
