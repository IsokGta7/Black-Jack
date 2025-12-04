#pragma once

#include <vector>

#include "Cartas.h"
#include "Utileria.h"
#include "Menu.h"

struct DealerSimulationResult {
    int total;
    std::vector<int> drawnCards;
};

int CalcularSumaLogica(const std::vector<int> &cartas, const Baraja &baraja);

DealerSimulationResult SimularJuegoDealer(const std::vector<int> &manoInicial, int pull, const Baraja &baraja);

int ActualizarOpcionMenu(int opcionActual, int tecla);

int ActualizarOpcionResultados(int opcionActual, int tecla);

