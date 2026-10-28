CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -I.

GAME_SOURCES := main.cpp Cartas.cpp GameLogic.cpp Menu.cpp Titulos.cpp Utileria.cpp
HEADERS := Cartas.h ColorConsola.h GameLogic.h Menu.h Titulos.h Utileria.h
GAME_BINARY := bin/Blackjack

TEST_BINARY := bin/tests/BlackjackTests
TEST_SOURCES := Cartas.cpp GameLogic.cpp Menu.cpp Titulos.cpp Utileria.cpp \
	tests/test_main.cpp tests/test_logic.cpp tests/test_layout.cpp

all: $(GAME_BINARY)

$(GAME_BINARY): $(GAME_SOURCES) $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(GAME_SOURCES)

$(TEST_BINARY): $(TEST_SOURCES) $(HEADERS) tests/doctest.h
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SOURCES)

.PHONY: test clean

test: $(TEST_BINARY)
	./$(TEST_BINARY)

clean:
	rm -rf bin/tests $(TEST_BINARY) $(GAME_BINARY)
