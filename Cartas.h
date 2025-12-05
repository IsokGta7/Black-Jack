#pragma once
#ifndef CARTAS_H_INCLUDED
#define CARTAS_H_INCLUDED

#include <string>

#include "Utileria.h"

struct ElementoLayout {
    int x;
    int y;
    int width;
    int height;
};

struct JuegoLayout {
    ElementoLayout titulo;
};

struct InstruccionesLayout {
    ElementoLayout titulo;
    ElementoLayout reglas;
    ElementoLayout okMarco;
    ElementoLayout okTexto;
};

struct ResultadosLayout {
    ElementoLayout marcoSolido;
    ElementoLayout marcoHueco;
    ElementoLayout tituloPerdio;
    ElementoLayout tituloGano;
    ElementoLayout tituloEmpate;
    ElementoLayout volver;
    ElementoLayout regresar;
    ElementoLayout marcoVolver;
    ElementoLayout marcoRegresar;
};

struct Carta {
    int palo; /**< El palo de la carta */
    int numero; /**< El nmero de la carta */
};
//***************************************************************************************************************************************************************************************************************************************
struct Baraja {
    Carta cartas[52]; /**< Arreglo de cartas para formar una baraja, como solo se utiliza una baraja se limita a 52 */
};
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcion para imprimir la pantalla de instrucciones.
 * \details Imprime y maneja toda la pantalla de instrucciones del programa.
 * \return void Imprime la pantalla de instrucciones.
 *
 */
void Instrucciones();
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcin para imprimir la pantalla del juego.
 * \details Imprime y maneja toda la pantalla de juego del programa.
 * \return void Imprime la pantalla del juego.
 *
 */
void Jugar();
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcion que maneja la impresin de una carta de una baraja inglesa
 * \details Imprime una carta en posicin (x,y) utilizando un marco de w x h dimensiones
 * \param x int Posicin x donde se va a imprimir
 * \param y int Posicin y donde se va a imprimir
 * \param w int Ancho de la carta
 * \param h int Altura de la carta
 * \param carta int ID de la carta en el arreglo de la estructura Baraja
 * \param baraja Baraja& Elemento Estructura de datos de la baraja
 * \return void Imprime la carta.
 *
 */
void ImprimirCarta(int x, int y, int w, int h, int carta, Baraja & baraja);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcin para imprimir la pantalla de crditos.
 * \details Imprime y maneja toda la pantalla de crditos del programa.
 * \return void Imprime la pantalla de crditos.
 *
 */
void Creditos();
//***************************************************************************************************************************************************************************************************************************************
/** \brief Llena una estructura de baraja con las cartas correspondientes
 * \details Toma una estructura de baraja de sus parametros y llena su arreglo de cartas con cartas correspondientes a las de una baraja inglesa.
 * \param baraja Baraja& Estructura de la baraja
 * \return void Modifica la estructura para agregar las cartas.
 *
 */
void LlenarBaraja(Baraja & baraja);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Revuelve el arreglo de cartas en una estructura de baraja.
 * \details Toma las cartas de la estructura baraja y cambia sus posiciones de forma aleatoria un nmero aleatorio de veces (entre 300 y 500).
 * \param baraja Baraja& Estructura de la baraja
 * \return void Modifica la estructura para revolver las cartas.
 *
 */
void Shuffle(Baraja & baraja);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime los iconos de las esquinas de una carta
 * \details Imprime el simbolo del palo y el nmero en la esquina superior izquierda y la esquina inferior derecha.
 * \param carta int ID de la carta en el arreglo de la estructura Baraja
 * \param x int Posicin x donde se va a imprimir
 * \param y int Posicin y donde se va a imprimir
 * \param w int Ancho de la carta
 * \param h int Altura de la carta
 * \param baraja Baraja& Estructura de la baraja
 * \param sibmolocarta std::string Simbolo correspondiente al palo de la carta
 * \param numerocarta std::string Letra/Nmero correspondiente a la carta
 * \return void Imprime el numero y palo en las esquinas de una carta
 *
 */
void ImprimirEsquinas(int carta, int x, int y, int w, int h, Baraja & baraja, std::string sibmolocarta, std::string numerocarta);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcin que determina el simbolo (en string) de una carta basado en el palo.
 * \details Dependiendo de los datos de la carta en la estructura Carta la funcin devuelve el smbolo del palo correspondiente.
 * \param carta int ID de la carta en el arreglo de la estructura Baraja
 * \param baraja Baraja& Estructura de la baraja
 * \return std::string Devuelve el simbolo de la carta.
 *
 */
std::string DeterminarSimbolo(int carta, Baraja & baraja);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcin que cambia el color en el que se imprimir una carta basado en el palo.
 * \details Dependiendo de los datos de la carta en la estructura Carta la funcin devuelve el smbolo del palo correspondiente.
 * \param carta int ID de la carta en el arreglo de la estructura Baraja
 * \param baraja Baraja& Estructura de la baraja
 * \return void Cambia el color en el que se imprime.
 *
 */
void DeterminarColor(int carta, Baraja & baraja);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcin que determina el nmero o rango (en string) de una carta basado en el palo.
 * \details Dependiendo de los datos de la carta en la estructura Carta la funcin devuelve la letra de la carta o el numero de la carta que se tiene que imprimir (en string).
 * \param carta int ID de la carta en el arreglo de la estructura Baraja
 * \param baraja Baraja& Estructura de la baraja
 * \return std::string Devuelve el rango de la carta.
 *
 */
std::string DeterminarRango(int carta, Baraja & baraja);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime los iconos del centro de una carta
 * \details Dependiendo del nmero (o rango) de la carta, imprime el patrn de simbolos del palo correspondiente en el centro de la carta.
 * \param carta int ID de la carta en el arreglo de la estructura Baraja
 * \param x int Posicin x donde se va a imprimir
 * \param y int Posicin y donde se va a imprimir
 * \param w int Ancho de la carta
 * \param h int Altura de la carta
 * \param baraja Baraja& Estructura de la baraja
 * \param sibmolocarta std::string Simbolo correspondiente al palo de la carta
 * \param rango int Nmero correspondiente a la carta
 * \return void Imprime los simbolos en el centro de una carta
 *
 */
void ImprimirCentro(int x, int y, int w, int h, std::string simbolo, int rango);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Calcula la suma de un arreglo de cartas
 * \details Usa el arreglo de IDs de cartas para tomar el valor nmerico de cada uno y calcular la puntuacin de esa mano (tambin determina si el as vale 1 u 11).
 * \param &cartas int* Arreglo de IDs de cartas
 * \param ncartas int Numero de cartas en el arreglo
 * \param baraja Baraja& Estructura de la baraja
 * \return int Puntuacin de la mano
 *
 */
int CalcularSuma(int * & cartas, int ncartas, Baraja & baraja);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Maneja el resultado e imprime la pantalla de resultados correspondientes.
 * \details Utilizando r determina que resultado se debe de imprimir en pantalla.
 * \param r int Resultado.
 * \return int Decisin para saber i se va a volver a jugar o no.
 *
 */
int Resultados(int r);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Funcin que simula el juego de la mano del Dealer.
 * \details Siguiendo las reglas del Blackjack se incrementa o planta la mano del Dealer y se devuelve la puntuacin.
 * \param &barajaD int* Arreglo de la baraja del Dealer
 * \param ncartas int Numero de cartas en la baraja del Dealer
 * \param baraja Baraja& Estructura de la baraja
 * \param pull int Cantidad de cartas que se han jalado de la baraja.
 * \return int Devuelve la puntuacin del Dealer
 *
 */
int JuegoDealer(int * & barajaD, int ncartas, Baraja & baraja, int pull);
//***************************************************************************************************************************************************************************************************************************************
enum {
    CORAZON = 0, /**< Carta de corazn */
        DIAMANTE, /**< Carta de diamante */
        TREBOL, /**< Carta de trebol */
        ESPADA /**< Carta de Espada */
};
//***************************************************************************************************************************************************************************************************************************************
enum {
    PERDIO = 0, /**< Resultado cuando el jugador pierde */
        GANO, /**< Resultado cuando el jugador gana */
        EMPATE /**< Resultado cuando ocurre un empate */
};
//***************************************************************************************************************************************************************************************************************************************
enum {
    PEDIR = 0, /**< Desicin del jugador para pedir una carta ms */
        PLANTAR /**< Desicin del jugador para terminar su mano y plantarse */
};
//***************************************************************************************************************************************************************************************************************************************
enum {
    AGAIN = 0, /**< Desicin del jugador para jugar de nuevo */
        SALIRJ /**< Desicin del jugador para dejar de jugar */
};

//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime la carta volteada de el dealer
 *
 * \param x int Posicion en x.
 * \param y int Posicion en y.
 * \return
 *
 */
void ImprimirCartaVolteada(int x, int y, int w, int h);

JuegoLayout CalcularLayoutJuego(const TerminalSize &tamano);
InstruccionesLayout CalcularLayoutInstrucciones(const TerminalSize &tamano);
ResultadosLayout CalcularLayoutResultados(const TerminalSize &tamano);

#endif // CARTAS_H_INCLUDED
