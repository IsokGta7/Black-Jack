#include "catch.hpp"

#include <vector>

#include "Cartas.h"

namespace {
bool Dentro(const ElementoLayout &el, const TerminalSize &tam) {
    return el.x >= 0 && el.y >= 0 && el.x + el.width <= tam.width && el.y + el.height <= tam.height;
}
}

TEST_CASE("Layouts stay within terminal bounds") {
    std::vector<TerminalSize> tamanios = {
        {220, 60},
        {120, 30},
        {80, 24}
    };

    for (const auto &tam : tamanios) {
        auto juego = CalcularLayoutJuego(tam);
        REQUIRE(Dentro(juego.titulo, tam));

        auto instrucciones = CalcularLayoutInstrucciones(tam);
        REQUIRE(Dentro(instrucciones.titulo, tam));
        REQUIRE(Dentro(instrucciones.reglas, tam));
        REQUIRE(Dentro(instrucciones.okMarco, tam));
        REQUIRE(Dentro(instrucciones.okTexto, tam));

        auto resultados = CalcularLayoutResultados(tam);
        REQUIRE(Dentro(resultados.marcoSolido, tam));
        REQUIRE(Dentro(resultados.marcoHueco, tam));
        REQUIRE(Dentro(resultados.tituloPerdio, tam));
        REQUIRE(Dentro(resultados.tituloGano, tam));
        REQUIRE(Dentro(resultados.tituloEmpate, tam));
        REQUIRE(Dentro(resultados.volver, tam));
        REQUIRE(Dentro(resultados.regresar, tam));
        REQUIRE(Dentro(resultados.marcoVolver, tam));
        REQUIRE(Dentro(resultados.marcoRegresar, tam));
    }
}
