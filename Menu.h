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
    JUGAR = 1, /**< Opci�n para jugar */
        INSTRUCCIONES = 2, /**< Opci�n para entrar a "Instrucciones" */
        CREDITOS = 3, /**< Opci�n para entrar a "Cr�ditos" */
        SALIR = 4 /**< Opci�n para salir de la aplicaci�n */
};
//***************************************************************************************************************************************************************************************************************************************

