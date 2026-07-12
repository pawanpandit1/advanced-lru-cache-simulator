CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
SRC = src/main.cpp
TARGET = lru_cache_simulator

all: $(TARGET)

$(TARGET): $(SRC) include/LRUCache.h
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
