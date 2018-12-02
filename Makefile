CXX=clang++
CXXFLAGS=-Wall -Wextra

BINDIR=bin

day1 : Day1/chronalCalibration.cpp Day1/repeatingCalibration.cpp
	$(CXX) Day1/chronalCalibration.cpp -o $(BINDIR)/chronalCalibration
	$(CXX) Day1/repeatingCalibration.cpp -o $(BINDIR)/repeatingCalibration

all: day1
