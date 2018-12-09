#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>

int main(){
	std::ifstream f("inputs/day7");
	char dependencie;
	char step;
	std::string voided;
	std::string line;

	std::map<char, std::set<char> > childs;
	std::map<char, std::set<char> > parent;

	std::set<char> avalaible;
	while(std::getline(f, line)){
		std::istringstream is(line);
		is  >> voided >> dependencie
			>> voided
			>> voided 
			>> voided
			>> voided 
			>> voided >> step;
		parent[step].insert(dependencie);
		childs[dependencie].insert(step);
	}

	for(char c = 'A'; c <= 'Z' ; ++c){
		if(parent.count(c) == 0 && childs.count(c) != 0){
			avalaible.insert(c);
		}
	}
	std::string output;
	while(!avalaible.empty()){
		char nextStep = *avalaible.begin();
		avalaible.erase(nextStep);
		output += nextStep;
		for(auto& children : childs[nextStep]){
			parent[children].erase(nextStep);
			if(parent[children].empty()){
				avalaible.insert(children);
			}
		}
	}
	std::cout << "Order : " << output << std::endl;
}
