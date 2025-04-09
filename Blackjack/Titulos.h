#pragma once
#ifndef TITULOS_H_INCLUDED
#define TITULOS_H_INCLUDED

/** \brief Imprime el titulo principal del programa
 * \details Imprime el titulo "BLACKJACK" utilizado en todas las pantallas
 * \return void Imprime en pantalla el título.
 *
 */
void ImprimirTitulo(int x, int i);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado para un resultado ganador.
 * \details Imprime el titulo "Ha ganado" utilizado en la impresión de resultados
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 *
 */
void ImprimirGanar(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado para un resultado perdedor.
 * \details Imprime el titulo "Ha perdido :(" utilizado en la impresión de resultados
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 *
 */
void ImprimirPerder(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado para un empate.
 * \details Imprime el titulo "Ha empatado!" utilizado en la impresión de resultados
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirEmpate(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado como opción en el menú principal.
 * \details Imprime el titulo "JUGAR" utilizado en el menú principal.
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirJugar(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado como opción en la sección de instrucciones.
 * \details Imprime el titulo "REGLAS" utilizado en la sección de instrucciones.
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirReglas(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado como opción en el menú principal.
 * \details Imprime el titulo "INSTRUCCIONES" utilizado en el menú principal.
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirInstrucciones(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado como opción en el menú principal.
 * \details Imprime el titulo "CRÉDITOS" utilizado en el menú principal.
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirCreditos(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado como opción en el menú principal.
 * \details Imprime el titulo "SALIR" utilizado en el menú principal.
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirSalir(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado en la sección de instrucciones.
 * \details Imprime el titulo "CONTROLES" utilizado en la sección de instrucciones.
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirControles(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
/** \brief Imprime el titulo utilizado en la sección de "Créditos".
 * \details Imprime el titulo "AUTORES" utilizado en la sección de "Créditos".
 * \param x int Posición x para la impresión.
 * \param y int Posición y para la impresión.
 * \return void Imprime en pantalla el título.
 */
void ImprimirAutores(int x, int y);
//***************************************************************************************************************************************************************************************************************************************
#endif // TITULOS_H_INCLUDED
