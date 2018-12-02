#include <iostream>
#include <fstream>

int main(){
	std::ifstream f("inputs/day1");
	int totalFreq = 0;
	int freq;
	while(f >> freq){
		totalFreq += freq;
	}
	std::cout << "Total frequence : " << totalFreq << std::endl;
}
