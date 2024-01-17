# Makefile for the enigma project

CXX = g++
CXXFLAGS = -std=c++11
SRC_FILES = test.cpp enigma.cpp
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
