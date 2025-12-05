#pragma once

#include <string>
#include <vector>

#include "Cartas.h"
#include "Utileria.h"
#include "Menu.h"

struct DealerSimulationResult {
    int total;
    std::vector<int> drawnCards;
};

enum class GameModeType {
    Clasico,
    Practica,
    Multironda,
    ManoCorta
};

struct GameMode {
    GameModeType tipo;
    std::string nombre;
    std::string descripcion;
    int maxCartasJugador;
    int maxCartasDealer;
    int rondas;
    int objetivo;
    int dealerSePlantaEn;
    bool practicaSinPerder;
    bool ganaPorMaxCartas;
};

struct GameSummary {
    GameMode modo;
    int resultadoFinal;
    int victorias;
    int empates;
    int derrotas;
    int rondasJugadas;
};

int CalcularSumaLogica(const std::vector<int> &cartas, const Baraja &baraja);

DealerSimulationResult SimularJuegoDealer(const std::vector<int> &manoInicial, int pull, const Baraja &baraja, const GameMode &modo);

int ActualizarOpcionMenu(int opcionActual, int tecla);

int ActualizarOpcionResultados(int opcionActual, int tecla);

const GameMode &ObtenerModoActual();
void CambiarModo(int direccion);
void SeleccionarModo(GameModeType tipo);
std::string FormatearModoResumen(const GameMode &modo);
int AjustarResultadoPorModo(int resultado, const GameMode &modo);
int DeterminarResultadoMano(int sumaJugador, int sumaDealer, int cartasJugador, int cartasDealer, const GameMode &modo);

