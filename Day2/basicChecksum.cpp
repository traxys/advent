#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

std::map<char, int> occCount(const std::string& s){
	std::map<char, int> occurences;
	for(auto chr : s){
		++occurences[chr];
	}
	return occurences;
}

bool hasValue(int value, const std::map<char, int>& mp){
	return std::any_of( mp.begin(),
						mp.end(),
						[value](std::pair<char, int> entry){
							return value == entry.second;
						});
}


int main(){
	std::ifstream f("inputs/day2");
	std::string label;
	int threeCount = 0;
	int twoCount = 0;
	while( f >> label){
		auto occurences = occCount(label);
		twoCount += hasValue(2, occurences);
		threeCount += hasValue(3, occurences);
	}
	std::cout << "Checksum : " << threeCount * twoCount 
		<< std::endl;
	return 0;
}
