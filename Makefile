CXX=clang++
CXXFLAGS=-Wall -Wextra

BINDIR=bin

day1 : Day1/chronalCalibration.cpp Day1/repeatingCalibration.cpp
	$(CXX) Day1/chronalCalibration.cpp -o $(BINDIR)/chronalCalibration
	$(CXX) Day1/repeatingCalibration.cpp -o $(BINDIR)/repeatingCalibration

day2 : Day2/basicChecksum.cpp Day2/findBoxLabel.cpp
	$(CXX) Day2/basicChecksum.cpp -o $(BINDIR)/basicChecksum
	$(CXX) Day2/findBoxLabel.cpp -o $(BINDIR)/findBoxLabel

all: day1 day2
