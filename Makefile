CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -I.

GAME_SOURCES := main.cpp Cartas.cpp GameLogic.cpp Menu.cpp Titulos.cpp Utileria.cpp
GAME_BINARY := bin/Blackjack

TEST_BINARY := bin/tests/BlackjackTests
TEST_SOURCES := GameLogic.cpp tests/test_logic.cpp

all: $(GAME_BINARY)

$(GAME_BINARY): $(GAME_SOURCES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(GAME_SOURCES)

$(TEST_BINARY): $(TEST_SOURCES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SOURCES)

.PHONY: test clean

test: $(TEST_BINARY)
	./$(TEST_BINARY)

clean:
	rm -rf bin/tests $(TEST_BINARY) $(GAME_BINARY)
