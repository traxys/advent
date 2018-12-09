#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

struct Worker{
	bool working;
	int timeLeft;
	char producing;

	Worker() : working(false), timeLeft(0), producing('.') {}
	
	void work(int timeSpent){
		if(working){
			timeLeft -= timeSpent;
		}
	}

	void setFinished(){
		working = false;
	}

	void produce(char res){
		if(working){
			std::cout << "Can't produce with working worker"
				<< std::endl;
		}
		working = true;
		producing = res;
		timeLeft = 60 + res - 64;
	}
};

int timeStep(const std::vector<Worker>& workers){
	int minTime = 120;
	for(auto& worker : workers){
		if(worker.timeLeft < minTime && worker.timeLeft != 0){
			minTime = worker.timeLeft;
		}
	}
	return minTime;
}

bool working(const std::vector<Worker>& workers){
	return std::any_of(workers.begin(),
				workers.end(),
				[](const Worker& worker){
					return worker.working;
				});
}

std::string waitingFor(char c,const std::set<char>& parents){
	std::string out;
	for(auto& parent : parents){
		out += parent;
	}
	return out;
}

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

	std::vector<Worker> workers;
	for(int i = 0; i < 5; ++i){
		workers.push_back(Worker());
	}
	int now = 0;
	while(!avalaible.empty() || working(workers)){
		for(auto& worker : workers){
			if(worker.working && worker.timeLeft == 0){
				worker.setFinished();
			}
			if(!worker.working){
				if(worker.producing != '.'){
					for(auto& children : childs[worker.producing]){
						parent[children].erase(worker.producing);
						if(parent[children].empty()){
							avalaible.insert(children);
						}
					}
					worker.producing = '.';
				}
				if(!avalaible.empty()){
					char nextStep = *avalaible.begin();
					worker.produce(nextStep);
					avalaible.erase(nextStep);
				}
			}
		}
		// second time to check if a worker has not liberated work
		for(auto& worker : workers){
			if(worker.working && worker.timeLeft == 0){
				worker.setFinished();
			}
			if(!worker.working){
				if(worker.producing != '.'){
					for(auto& children : childs[worker.producing]){
						parent[children].erase(worker.producing);
						if(parent[children].empty()){
							avalaible.insert(children);
						}
					}
					worker.producing = '.';
				}
				if(!avalaible.empty()){
					char nextStep = *avalaible.begin();
					worker.produce(nextStep);
					avalaible.erase(nextStep);
				}
			}
		}
		std::cout << now << "\t";
		for(auto& worker : workers){
			std::cout << worker.producing << "\t";
		}
		std::cout << std::endl;

		/*auto tms = timeStep(workers);
		now += tms;
		for(auto& worker : workers){
			worker.work(tms);
		}*/
		now++;
		for(auto& worker : workers){
			worker.work(1);
		}
	}
	for(auto& process : parent){
		if(!process.second.empty()){
			std::cout << process.first << " was not done, deps on :";
			for(auto& dp : process.second){
				std::cout << dp;
			}
			std::cout << std::endl;
		}
	}
	std::cout << "Time taken : " << now - 1 << std::endl;
}
