#include <map>
#include <iostream>
#include <fstream>
#include <cmath>

bool isOppositeCase(const char& a,const char&b){
	return abs(a-b) == 32;	
}

bool isSame(const char& a,const char &b){
	return isOppositeCase(a,b) || (a==b);
}

int main(){
	std::ifstream f("inputs/day5");
	// Map of [removed char] to [polymer for it]
	std::map<char, std::string> currentPolymers;
	char newSpecies;
	while(f >> newSpecies){
		for(char c = 'a'; c <= 'z' ; ++c){
			if(!isSame(c,newSpecies)){
					if(isOppositeCase(newSpecies,
									  currentPolymers[c].back())){
					currentPolymers[c].pop_back();
					}
					else{
					currentPolymers[c].push_back(newSpecies);
					}
			}
		}
	}
	
	char minChar = '@';
	int minLength  = 50000;
	for(auto& polymer : currentPolymers){
		if(polymer.second.size() < minLength){
			minChar = polymer.first;
			minLength = polymer.second.size();
		}
	}
	std::cout << " Smallest chain is : " << minLength << 
		" by removing " << minChar << std::endl;  
}
