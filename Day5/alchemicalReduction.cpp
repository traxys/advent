#include <iostream>
#include <fstream>
#include <cmath>

bool isOppositeCase(const char& a,const char&b){
	return abs(a-b) == 32;	
}

int main(){
	std::ifstream f("inputs/day5");
	std::string currentPolymer;
	char newSpecies;
	while(f >> newSpecies){
		if(isOppositeCase(newSpecies, currentPolymer.back())){
			currentPolymer.pop_back();
		}
		else{
			currentPolymer.push_back(newSpecies);
		}
	}
	std::cout << "Final length is " << currentPolymer.size() << 
		std::endl;
}
