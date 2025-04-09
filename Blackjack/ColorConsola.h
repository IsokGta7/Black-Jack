#pragma once
#ifndef COLORCONSOLA_H_INCLUDED
#define COLORCONSOLA_H_INCLUDED

#include <iostream>
#include <windows.h>

/** \brief Esta funcion declara el color azul
 *
 * \param s std::ostream& Regresa la posicion de lo que esta en el flujo con el color editado
 * \return std::ostream&
 *
 */
inline std::ostream & blue(std::ostream & s) //Esta funcion declara el color azul para ser utilizado en el stream
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}
//***************************************************************************************************************************************************************************************************************************************
/** \brief Esta funcion declara el color rojo
 *
 * \param s std::ostream& Regresa la posicion de lo que esta en el flujo con el color editado
 * \return std::ostream&
 *
 */
inline std::ostream & red(std::ostream & s) //Esta funcion declara el color rojo para ser utilizado en el stream
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}
//***************************************************************************************************************************************************************************************************************************************
/** \brief Esta funcion declara el color verde
 *
 * \param s std::ostream& Regresa la posicion de lo que esta en el flujo con el color editado
 * \return std::ostream&
 *
 */
inline std::ostream & green(std::ostream & s) //Esta funcion declara el color verde para ser utilizado en el stream
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}
//***************************************************************************************************************************************************************************************************************************************
/** \brief Esta funcion declara el color amarillo
 *
 * \param s std::ostream& Regresa la posicion de lo que esta en el flujo con el color editado
 * \return std::ostream&
 *
 */
inline std::ostream & yellow(std::ostream & s) //Esta funcion declara el color amarillo para ser utilizado en el stream
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}
//***************************************************************************************************************************************************************************************************************************************
/** \brief Esta funcion declara el color blanco
 *
 * \param s std::ostream& Regresa la posicion de lo que esta en el flujo con el color editado
 * \return std::ostream&
 *
 */
inline std::ostream & white(std::ostream & s) //Esta funcion declara el color blanco para ser utilizado en el stream
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}
//***************************************************************************************************************************************************************************************************************************************
#endif // COLORCONSOLA_H_INCLUDED
