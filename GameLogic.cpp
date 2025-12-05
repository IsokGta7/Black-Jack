#include "GameLogic.h"

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

namespace {

std::vector<GameMode> CrearModos() {
    return {
        {GameModeType::Clasico, "Clásico", "Una mano estándar de blackjack.", 5, 5, 1, 21, 17, false, true},
        {GameModeType::Practica, "Práctica", "No cuenta derrotas; ideal para aprender.", 5, 5, 1, 21, 17, true, true},
        {GameModeType::Multironda, "Multironda", "Juega una serie al mejor de tres manos.", 5, 5, 3, 21, 17, false, true},
        {GameModeType::ManoCorta, "Mano corta", "Límite de cartas más estricto y objetivo reducido.", 3, 4, 1, 18, 16, false, false},
    };
}

std::vector<GameMode> modos = CrearModos();
size_t modoIndex = 0;

int AjustarIndice(int indice, int total) {
    int normalizado = indice % total;
    if (normalizado < 0) normalizado += total;
    return normalizado;
}

}  // namespace

int CalcularSumaLogica(const std::vector<int> &cartas, const Baraja &baraja) {
    int suma = 0;
    int nas = 0;
    for (int carta : cartas) {
        int numero = baraja.cartas[carta].numero;
        if (numero == 1) {
            suma += 11;
            nas++;
        } else if (numero >= 11) {
            suma += 10;
        } else {
            suma += numero;
        }
    }

    while (suma > 21 && nas > 0) {
        suma -= 10;
        nas--;
    }

    return suma;
}

DealerSimulationResult SimularJuegoDealer(const std::vector<int> &manoInicial, int pull, const Baraja &baraja, const GameMode &modo) {
    DealerSimulationResult result{0, {}};
    std::vector<int> mano = manoInicial;
    result.total = CalcularSumaLogica(mano, baraja);

    while (result.total < modo.dealerSePlantaEn && static_cast<int>(mano.size()) < modo.maxCartasDealer && pull < 52) {
        mano.push_back(pull);
        result.drawnCards.push_back(pull);
        result.total = CalcularSumaLogica(mano, baraja);
        pull++;
    }

    return result;
}

int ActualizarOpcionMenu(int opcionActual, int tecla) {
    if (tecla == UP) {
        return opcionActual == JUGAR ? SALIR : opcionActual - 1;
    }
    if (tecla == DOWN) {
        return opcionActual == SALIR ? JUGAR : opcionActual + 1;
    }
    return opcionActual;
}

int ActualizarOpcionResultados(int opcionActual, int tecla) {
    if (tecla == RIGHT) {
        return SALIRJ;
    }
    if (tecla == LEFT) {
        return AGAIN;
    }
    return opcionActual;
}

void LlenarBaraja(Baraja &baraja) {
    int j = 0;
    for (int k = 0; k < 4; k++) {
        for (int i = 1; i <= 13; i++) {
            baraja.cartas[j].palo = k;
            baraja.cartas[j].numero = i;
            j++;
        }
    }
}

void Shuffle(Baraja &baraja) {
    int x, y, paloaux, numeroaux;
    int i = rand() % 500 + 300;
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

int CalcularSuma(int *&cartas, int ncartas, Baraja &baraja) {
    std::vector<int> mano(cartas, cartas + ncartas);
    return CalcularSumaLogica(mano, baraja);
}

const GameMode &ObtenerModoActual() {
    return modos[modoIndex];
}

void CambiarModo(int direccion) {
    modoIndex = AjustarIndice(static_cast<int>(modoIndex) + direccion, static_cast<int>(modos.size()));
}

void SeleccionarModo(GameModeType tipo) {
    for (size_t i = 0; i < modos.size(); ++i) {
        if (modos[i].tipo == tipo) {
            modoIndex = i;
            return;
        }
    }
}

std::string FormatearModoResumen(const GameMode &modo) {
    std::string resumen = modo.nombre + " - " + modo.descripcion + " Objetivo " + std::to_string(modo.objetivo);
    resumen += ", rondas " + std::to_string(modo.rondas) + ", max J " + std::to_string(modo.maxCartasJugador);
    resumen += ", max D " + std::to_string(modo.maxCartasDealer);
    return resumen;
}

int AjustarResultadoPorModo(int resultado, const GameMode &modo) {
    if (modo.practicaSinPerder && resultado == PERDIO) return EMPATE;
    return resultado;
}

int DeterminarResultadoMano(int sumaJugador, int sumaDealer, int cartasJugador, int cartasDealer, const GameMode &modo) {
    (void)cartasDealer;
    if (sumaJugador > modo.objetivo) return AjustarResultadoPorModo(PERDIO, modo);
    if (sumaJugador == modo.objetivo) return AjustarResultadoPorModo(GANO, modo);
    if (modo.ganaPorMaxCartas && cartasJugador >= modo.maxCartasJugador && sumaJugador < modo.objetivo) {
        return AjustarResultadoPorModo(GANO, modo);
    }
    if (sumaDealer > modo.objetivo) return AjustarResultadoPorModo(GANO, modo);
    if (sumaJugador > sumaDealer) return AjustarResultadoPorModo(GANO, modo);
    if (sumaDealer > sumaJugador) return AjustarResultadoPorModo(PERDIO, modo);
    return AjustarResultadoPorModo(EMPATE, modo);
}

