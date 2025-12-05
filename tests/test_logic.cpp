#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <set>
#include <string>
#include <vector>

#include "GameLogic.h"
#include "Menu.h"
#include "Utileria.h"

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

    SeleccionarModo(GameModeType::Clasico);
    const GameMode &modo = ObtenerModoActual();

    std::vector<int> manoInicial = {9, 6};
    DealerSimulationResult resultado = SimularJuegoDealer(manoInicial, 20, baraja, modo);

    REQUIRE(resultado.total == 17);
    REQUIRE(resultado.drawnCards.empty());
}

TEST_CASE("Dealer pide hasta cinco cartas si es necesario") {
    Baraja baraja;
    LlenarBaraja(baraja);

    const GameMode &modo = ObtenerModoActual();

    std::vector<int> manoInicial = {1, 2};
    DealerSimulationResult resultado = SimularJuegoDealer(manoInicial, 3, baraja, modo);

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

TEST_CASE("Selección de modos avanza y se puede fijar por tipo") {
    SeleccionarModo(GameModeType::Clasico);
    const std::string clasico = ObtenerModoActual().nombre;

    CambiarModo(1);
    REQUIRE(ObtenerModoActual().nombre != clasico);

    SeleccionarModo(GameModeType::Multironda);
    REQUIRE(ObtenerModoActual().tipo == GameModeType::Multironda);
}

TEST_CASE("Prctica convierte las derrotas en empates") {
    SeleccionarModo(GameModeType::Practica);
    const GameMode &modo = ObtenerModoActual();
    REQUIRE(AjustarResultadoPorModo(PERDIO, modo) == EMPATE);
}

TEST_CASE("Modo de mano corta limita cartas del dealer y usa objetivo reducido") {
    SeleccionarModo(GameModeType::ManoCorta);
    const GameMode &modo = ObtenerModoActual();

    Baraja baraja;
    LlenarBaraja(baraja);
    std::vector<int> manoDealer = {0};
    DealerSimulationResult resultado = SimularJuegoDealer(manoDealer, 5, baraja, modo);
    REQUIRE(static_cast<int>(resultado.drawnCards.size()) <= modo.maxCartasDealer - 1);

    int resultadoRonda = DeterminarResultadoMano(17, 16, modo.maxCartasJugador, 2, modo);
    REQUIRE(resultadoRonda == GANO);
}

#ifdef _WIN32
TEST_CASE("Códigos extendidos de _getch se traducen a constantes internas") {
    REQUIRE(TraducirCodigoExtendidoWindows(224, 72) == UP);
    REQUIRE(TraducirCodigoExtendidoWindows(224, 80) == DOWN);
    REQUIRE(TraducirCodigoExtendidoWindows(224, 75) == LEFT);
    REQUIRE(TraducirCodigoExtendidoWindows(224, 77) == RIGHT);
    REQUIRE(TraducirCodigoExtendidoWindows(0, ENTER) == ENTER);
}
#endif

TEST_CASE("Navegacin de resultados cambia izquierda/derecha") {
    int opcion = AGAIN;
    opcion = ActualizarOpcionResultados(opcion, RIGHT);
    REQUIRE(opcion == SALIRJ);

    opcion = ActualizarOpcionResultados(opcion, LEFT);
    REQUIRE(opcion == AGAIN);
}

