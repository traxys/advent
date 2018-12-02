#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

int differenceCount(const std::string& s1, const std::string& s2){
	if( s1.size() != s2.size()){
		throw std::runtime_error("Not same sized strings");
	}
	int total = 0;
	for(size_t i = 0; i < s1.size(); ++i){
		total += (s1[i] != s2[i]);
	}
	return total;
}

int main(){
	std::ifstream f("inputs/day2");
	std::string label;
	std::vector<std::string> labels;
	
	while(f >> label){
		labels.push_back(label);
	}
	for(auto& label1 : labels){
		auto it = std::find_if( labels.begin(),
					  labels.end(),
					  [label1](const std::string& label2){
							return differenceCount(label1, label2)
									== 1;
					  });
		if(it != labels.end()){
			std::cout << " Matching labels : " << std::endl
					  << label1 << std::endl
					  << *it << std::endl;
			break;
		}
	}
	return 0;
}
