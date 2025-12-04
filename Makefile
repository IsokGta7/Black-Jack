CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -I.

TEST_BINARY := bin/tests/BlackjackTests
TEST_SOURCES := GameLogic.cpp tests/test_logic.cpp

$(TEST_BINARY): $(TEST_SOURCES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SOURCES)

.PHONY: test clean

test: $(TEST_BINARY)
	./$(TEST_BINARY)

clean:
	rm -rf bin/tests $(TEST_BINARY)
