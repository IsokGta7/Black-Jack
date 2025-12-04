#include "GameLogic.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

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

DealerSimulationResult SimularJuegoDealer(const std::vector<int> &manoInicial, int pull, const Baraja &baraja) {
    DealerSimulationResult result{0, {}};
    std::vector<int> mano = manoInicial;
    result.total = CalcularSumaLogica(mano, baraja);

    while (result.total <= 16 && mano.size() < 5 && pull < 52) {
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

