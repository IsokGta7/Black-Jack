#pragma once


#include <string>

/** \brief Aqui se tiene todo el codigo del menu principal.
 *
 * \return int Regresa la opcion elegida para saber que hacer.
 *
 */
int Menu();
//***************************************************************************************************************************************************************************************************************************************
enum {
    JUGAR = 1, /**< Opción para jugar */
        INSTRUCCIONES = 2, /**< Opción para entrar a "Instrucciones" */
        CREDITOS = 3, /**< Opción para entrar a "Créditos" */
        SALIR = 4 /**< Opción para salir de la aplicación */
};
//***************************************************************************************************************************************************************************************************************************************

