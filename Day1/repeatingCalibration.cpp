#include <fstream>
#include <vector>
#include <iostream>
#include <set>

int main(){
	std::ifstream f("inputs/day1");
	int totalFreq = 0;
	int freq;
	std::set<int> seenFreq;
	seenFreq.insert(0);
	std::vector<int> freqs;
	
	while( f >> freq){
		freqs.push_back(freq);
	}

	int freqCount = freqs.size();
	int index = 0;
	
	while(true){
		int newFreq = totalFreq + freqs[index];
		if(seenFreq.count(newFreq) == 1){
			std::cout << "Repeated frequencie : " << newFreq
				<< std::endl;
			break;
		}
		else{
			seenFreq.insert(newFreq);
			totalFreq = newFreq;
			index = (index + 1) % freqCount;
		}
	}
}
