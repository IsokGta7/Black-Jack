#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <set>
#include <vector>

#include "GameLogic.h"
#include "Menu.h"

TEST_CASE("CalcularSuma handles ace high and low") {
    Baraja baraja;
    LlenarBaraja(baraja);

    std::vector<int> manoConAceYDiez = {0, 8};
    REQUIRE(CalcularSumaLogica(manoConAceYDiez, baraja) == 20);

    std::vector<int> manoConAceYFiguras = {0, 11, 12};
    REQUIRE(CalcularSumaLogica(manoConAceYFiguras, baraja) == 21);

    std::vector<int> dosAsesYNueve = {0, 13, 8};
    REQUIRE(CalcularSumaLogica(dosAsesYNueve, baraja) == 21);
}

TEST_CASE("Shuffle mantiene las 52 cartas en rango") {
    Baraja baraja;
    LlenarBaraja(baraja);

    std::vector<std::pair<int, int>> original;
    for (const auto &carta : baraja.cartas) {
        original.emplace_back(carta.palo, carta.numero);
    }

    Shuffle(baraja);

    std::multiset<std::pair<int, int>> despues;
    for (const auto &carta : baraja.cartas) {
        REQUIRE(carta.palo >= 0);
        REQUIRE(carta.palo < 4);
        REQUIRE(carta.numero >= 1);
        REQUIRE(carta.numero <= 13);
        despues.insert({carta.palo, carta.numero});
    }

    REQUIRE(despues.size() == original.size());
    REQUIRE((despues == std::multiset<std::pair<int, int>>(original.begin(), original.end())));
}

TEST_CASE("Dealer se planta en 17 o ms") {
    Baraja baraja;
    LlenarBaraja(baraja);

    std::vector<int> manoInicial = {9, 6};
    DealerSimulationResult resultado = SimularJuegoDealer(manoInicial, 20, baraja);

    REQUIRE(resultado.total == 17);
    REQUIRE(resultado.drawnCards.empty());
}

TEST_CASE("Dealer pide hasta cinco cartas si es necesario") {
    Baraja baraja;
    LlenarBaraja(baraja);

    std::vector<int> manoInicial = {1, 2};
    DealerSimulationResult resultado = SimularJuegoDealer(manoInicial, 3, baraja);

    REQUIRE(resultado.drawnCards.size() >= 1);
    REQUIRE(resultado.drawnCards.size() <= 3);
    REQUIRE(resultado.total >= 17);
}

TEST_CASE("Navegacin del men envuelve arriba y abajo") {
    int opcion = JUGAR;
    opcion = ActualizarOpcionMenu(opcion, UP);
    REQUIRE(opcion == SALIR);

    opcion = ActualizarOpcionMenu(opcion, DOWN);
    REQUIRE(opcion == JUGAR);

    opcion = ActualizarOpcionMenu(opcion, DOWN);
    REQUIRE(opcion == INSTRUCCIONES);
}

TEST_CASE("Navegacin de resultados cambia izquierda/derecha") {
    int opcion = AGAIN;
    opcion = ActualizarOpcionResultados(opcion, RIGHT);
    REQUIRE(opcion == SALIRJ);

    opcion = ActualizarOpcionResultados(opcion, LEFT);
    REQUIRE(opcion == AGAIN);
}

