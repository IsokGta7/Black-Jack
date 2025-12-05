#pragma once
#ifndef UTILERIA_H_INCLUDED
#define UTILERIA_H_INCLUDED

#include <string>

struct TerminalSize {
    int width;
    int height;
};

struct AnimacionConfig {
    bool habilitada;
    int retardoPasoMs;
};

// Conjunto de caracteres Unicode que reemplazan los códigos dependientes de página de códigos.
inline constexpr const char *BOX_VERTICAL = u8"│";
inline constexpr const char *BOX_HORIZONTAL = u8"─";
inline constexpr const char *BOX_TOP_RIGHT = u8"┐";
inline constexpr const char *BOX_BOTTOM_LEFT = u8"└";
inline constexpr const char *BOX_BOTTOM_RIGHT = u8"┘";
inline constexpr const char *BOX_TOP_LEFT = u8"┌";
inline constexpr const char *BOX_DOUBLE_VERTICAL = u8"║";
inline constexpr const char *BOX_DOUBLE_HORIZONTAL = u8"═";
inline constexpr const char *BOX_DOUBLE_TOP_RIGHT = u8"╗";
inline constexpr const char *BOX_DOUBLE_BOTTOM_LEFT = u8"╚";
inline constexpr const char *BOX_DOUBLE_BOTTOM_RIGHT = u8"╝";
inline constexpr const char *BOX_DOUBLE_TOP_LEFT = u8"╔";
inline constexpr const char *CARD_BACK_FILL = u8"░";

/** Cambia la posición del cursor. */
void MoverCursor(short x, short y);

/** Ajusta la dimensión de la ventana si la plataforma lo permite. */
void CambiarTamanio(int w, int h);

/** Imprime un marco hueco de w por h dimensiones en la posición (x,y). */
void DibujarMarco(int w, int h, int x, int y);

/** Elimina un marco de W x H dimensiones. */
void BorrarMarco(int w, int h, int x, int y);

/** Crea un arreglo dinámico de tamaño dim. */
int * CrearArreglo(int dim);

/** Libera la memoria de un arreglo creado con CrearArreglo. */
void DestruirArreglo(int * & ary);

enum {
    ENTER = 13, /**< Valor capturado por getch() al presionar la tecla enter */
    UP = 72, /**< Valor capturado por getch() al presionar la flecha direccional hacia arriba*/
    DOWN = 80, /**< Valor capturado por getch() al presionar la flecha direccional hacia abajo*/
    LEFT = 75, /**< Valor capturado por getch() al presionar la flecha direccional hacia la izquierda*/
    RIGHT = 77 /**< Valor capturado por getch() al presionar la flecha direccional hacia la derecha*/
};

#ifdef _WIN32
/** Traduce el código extendido de _getch() a los valores internos usados en el juego. */
inline int TraducirCodigoExtendidoWindows(int /*prefijo*/, int codigoTecla) {
    switch (codigoTecla) {
    case 72:
        return UP;
    case 80:
        return DOWN;
    case 75:
        return LEFT;
    case 77:
        return RIGHT;
    default:
        return codigoTecla;
    }
}
#endif

/** Muestra u oculta el cursor. */
void set_cursor(bool visible);

/** Dibuja un marco con relleno para tapar las cartas. */
void DibujarMarcoSolido(int w, int h, int x, int y);

/** Imprime una animación de aparición vertical con sombreado suave. */
void AnimarAparicionRectangular(int x, int y, int w, int h);

/** Configura la animación global desde variables de entorno. */
void ConfigurarAnimacionesDesdeEntorno();

/** Activa o desactiva la animación durante la ejecución. */
void EstablecerAnimacionesHabilitadas(bool habilitar);

/** Devuelve la configuración actual de animación. */
AnimacionConfig ObtenerConfiguracionAnimacion();

/** Limpia la pantalla de la consola de forma multiplataforma. */
void LimpiarPantalla();

/** Ajusta el título de la consola. */
void ActualizarTitulo(const std::string &titulo);

/** Configura la salida en UTF-8 cuando la plataforma lo requiere. */
void ConfigurarCodificacion();

/** Espera la cantidad de milisegundos indicada sin bloquear la interfaz. */
void EsperarMilisegundos(int milisegundos);

/** Lee una tecla sin eco, con soporte para flechas en plataformas POSIX y Windows. */
int LeerTecla();

/** Obtiene el tamaño visible actual de la terminal. */
TerminalSize ObtenerTamanoTerminal();

/** Calcula una posición centrada para un elemento del ancho indicado. */
int CentrarEnDimension(int dimensionTotal, int dimensionContenido);

#endif // UTILERIA_H_INCLUDED
