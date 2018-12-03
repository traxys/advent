CXX=clang++
CXXFLAGS=-Wall -Wextra

BINDIR=bin

all: day1 day2

day1 : Day1/chronalCalibration.cpp Day1/repeatingCalibration.cpp
	$(CXX) Day1/chronalCalibration.cpp -o $(BINDIR)/chronalCalibration
	$(CXX) Day1/repeatingCalibration.cpp -o $(BINDIR)/repeatingCalibration

day2 : Day2/basicChecksum.cpp Day2/findBoxLabel.cpp
	$(CXX) Day2/basicChecksum.cpp -o $(BINDIR)/basicChecksum
	$(CXX) Day2/findBoxLabel.cpp -o $(BINDIR)/findBoxLabel

day3 : Day3/overlappingSlices.cpp
	$(CXX) Day3/overlappingSlices.cpp -o $(BINDIR)/overlappingSlices
