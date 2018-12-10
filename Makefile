CXX=clang++
CXXFLAGS=-Wall -Wextra

BINDIR=bin

day10: Day10/floatingText.cpp
	$(CXX) Day10/floatingText.cpp -o $(BINDIR)/floatingText

day9: Day9/marbleCircle.cpp
	$(CXX) Day9/marbleCircle.cpp -o $(BINDIR)/marbleCircle

day8: Day8/treeSummation.cpp
	$(CXX) Day8/treeSummation.cpp -o $(BINDIR)/treeSummation

day7: Day7/complicatedPlanning.cpp Day7/sharedPlanning.cpp
	$(CXX) Day7/complicatedPlanning.cpp -o $(BINDIR)/complicatedPlanning
	$(CXX) Day7/sharedPlanning.cpp -o $(BINDIR)/sharedPlanning

day6: Day6/largestNeighbouring.cpp
	$(CXX) Day6/largestNeighbouring.cpp -o $(BINDIR)/largestNeighbouring

day5: Day5/alchemicalReduction.cpp Day5/alchemicalTriming.cpp
	$(CXX) Day5/alchemicalReduction.cpp -o $(BINDIR)/alchemicalReduction
	$(CXX) Day5/alchemicalTriming.cpp -o $(BINDIR)/alchemicalTriming

day4: Day4/sleepingGuards.cpp Day4/sleepingMinutes.cpp
	$(CXX) Day4/sleepingMinutes.cpp -o $(BINDIR)/sleepingMinutes
	$(CXX) Day4/sleepingGuards.cpp -o $(BINDIR)/sleepingGuards

day1 : Day1/chronalCalibration.cpp Day1/repeatingCalibration.cpp
	$(CXX) Day1/chronalCalibration.cpp -o $(BINDIR)/chronalCalibration
	$(CXX) Day1/repeatingCalibration.cpp -o $(BINDIR)/repeatingCalibration

day2 : Day2/basicChecksum.cpp Day2/findBoxLabel.cpp
	$(CXX) Day2/basicChecksum.cpp -o $(BINDIR)/basicChecksum
	$(CXX) Day2/findBoxLabel.cpp -o $(BINDIR)/findBoxLabel

day3 : Day3/overlappingSlices.cpp
	$(CXX) Day3/overlappingSlices.cpp -o $(BINDIR)/overlappingSlices

all: day1 day2 day3 day4 day5 day6 day7 day8 day9 day10

clean:
	rm $(BINDIR)/*
