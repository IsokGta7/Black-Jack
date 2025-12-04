#pragma once
#ifndef UTILERIA_H_INCLUDED
#define UTILERIA_H_INCLUDED

/** \brief Cambia la posici&acute;ón del cursor.
 * \details Mueve el cursor a x, y para comenzar a imprimir desde ahí.
 * \param x Coordenada x a la que se va a mover
 * \param y Coordenada y a la que se va a mover
 * \return Mueve el cursor.
 *
 */
void MoverCursor(short x, short y);
//******************************************************************************************************************************
/*********************************************************************************************************/
/** \brief Cambia la dimensión de la ventana.
 * \details Cambia la dimensión de la ventana a w ancho y h de alto.
 * \param w Ancho de la ventana
 * \param h Altura de la ventana
 * \return Cambia el tamaño de la ventana a w anchura y h altura.
 *
 */
void CambiarTamanio(int w, int h);
//******************************************************************************************************************************
/*********************************************************************************************************/
/** \brief Imprime un marco de w por h dimensiones en la posicion (x,y)
 * \details Imprime un cuadrilatéro hueco utilizando caractéres Unicode de x por y dimensiones.
 * \param w El ancho del marco.
 * \param h La altura del marco.
 * \param x short Posicion x para imprimir.
 * \param y short Posicion y para imprimir.
 * \return Imprime el marco de w por h en la pantalla
 *
 */
void DibujarMarco(int w, int h, int x, int y);
//******************************************************************************************************************************
/*********************************************************************************************************/
/** \brief Elimina un marco de W x H dimensiones
 * \details Imprime caracteres en blanco de la misma manera en la que "DibujarMarco" dibuja un marco para "borrar" el marco de la pantalla.
 * \param w El ancho del marco.
 * \param h La altura del marco.
 * \param x short Posicion x para imprimir.
 * \param y short Posicion y para imprimir.
 * \return void Elimina el marco de w x h dimensiones en la posicion (x,y).
 *
 */
void BorrarMarco(int w, int h, int x, int y);
//******************************************************************************************************************************
/*********************************************************************************************************/
/** \brief Crea un arreglo dinamico de tamaño dim
 * \details Crea y devuelve un arreglo unidimiensional creado en el heap.
 * \param dim int Dimension del arreglo
 * \return int* Arreglo creado
 *
 */
int * CrearArreglo(int dim);
//******************************************************************************************************************************
/*********************************************************************************************************/
/** \brief Elimina y limpia la memoria del Heap en la que se encuentra un arreglo
 * \details Utilizando la direccion de un arreglo creado utilizando la funcion CrearArreglo elimina y libera el Heap de ese arreglo.
 * \param &ary int* Puntero del arreglo
 * \return Limpia el Heap
 *
 */
void DestruirArreglo(int * & ary);
//******************************************************************************************************************************
/*********************************************************************************************************/
static const wchar_t BV = L'│'; /**< Barra vertical */
static const wchar_t ESD = L'┐'; /**< Esquina superior derecha de un marco */
static const wchar_t EII = L'└'; /**< Esquina inferior izquierda de un marco */
static const wchar_t BH = L'─'; /**< Barra horizontal */
static const wchar_t EID = L'┘'; /**< Esquina inferior derecha de un marco */
static const wchar_t ESI = L'┌'; /**< Esquina superior izquierda de un marco */
static const wchar_t CV = L'░'; /**< Relleno de las cartas volteadas */
//******************************************************************************************************************************
/*********************************************************************************************************/
enum {
    ENTER = 13, /**< Valor capturado por getch() al presionar la tecla enter */
        UP = 72, /**< Valor capturado por getch() al presionar la flecha direccional hacia arriba*/
        DOWN = 80, /**< Valor capturado por getch() al presionar la flecha direccional hacia abajo*/
        LEFT = 75, /**< Valor capturado por getch() al presionar la flecha direccional hacia la izquierda*/
        RIGHT = 77 /**< Valor capturado por getch() al presionar la flecha direccional hacia la derecha*/
};
//******************************************************************************************************************************
/*********************************************************************************************************/
/** \brief Esconde el cursor
 *
 * \param visible bool El valor que recibe para saber si aparecera el cursor
 * \return void no regresa nada
 *
 */
void set_cursor(bool visible);
//******************************************************************************************************************************
/*********************************************************************************************************/
/** \brief Dibuja un marco que tiene un fondo para tapar las cartas.
 *
 * \param w int Cantidad de ancho del marco.
 * \param h int Cantidad de alto del marco.
 * \param x int Cantidad en x del marco.
 * \param y int Cantidad en y del marco.
 * \return void
 *
 */
void DibujarMarcoSolido(int w, int h, int x, int y);

#endif // UTILERIA_H_INCLUDED
