#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

enum status{
	wake,
	sleep,
	onDuty,
	invalid
};

struct entry{
	int year, month, day;
	int hour, mins;
	status stat;
	std::string guardID;

	std::string repr() const{
		std::ostringstream s;
		s << year << "-" << month << "-" << day <<
			" | " << hour << ":" << mins << " ["<< guardID;
		switch(stat){
			case wake:
				s << " wakes up ]";
				break;
			case sleep:
				s << " falls asleep ]";
				break;
			case onDuty:
				s << " is on duty]";
				break;
			case invalid:
				s << " does an invalid action]";
				break;
		}
		return s.str();
	}
};

inline bool operator< (const entry& lhs, const entry& rhs){
	if(lhs.year == rhs.year){
		if(lhs.month == rhs.month){
			if(lhs.day == rhs.day){
				if(lhs.hour == rhs.hour){
					return lhs.mins < rhs.mins;
				}else{
					return lhs.hour < rhs.hour;
				}
			}else{
				return lhs.day < rhs.day;
			}
		}else{
			return lhs.month < rhs.month;
		}
	}else{
		return lhs.year < rhs.year;
	}
}

struct guard{
	std::string id;
	bool isAsleep;
	int timeFellAsleep;
	int sleepingTime;

	guard() : id("@"), isAsleep(false),
							 timeFellAsleep(0), sleepingTime(0) {};
	guard(const std::string& id_) : id(id_), isAsleep(false),
							 timeFellAsleep(0), sleepingTime(0) {};
};

int main(){
	std::ifstream f("inputs/day4");
	std::string line;

	std::vector<entry> entries;
	std::map<std::string, guard> guards;

	while(std::getline(f, line)){
		std::istringstream is(line);
		char voided;
		int year, month, day;
		int hour, mins;
		std::string message;
		is >> voided >> year >> voided >> month >> voided >> day
		   >> hour >> voided >> mins >> voided >> message;
		entry current = {year, month, day, hour, mins, invalid, "@"};
		if(message == "Guard"){
			current.stat = onDuty;
			std::string id;
			is >> id;
			current.guardID = id;
		}
		if(message == "falls"){
			current.stat = sleep;
		}
		if(message == "wakes"){
			current.stat = wake;
		}
		entries.push_back(current);
	}
	std::sort(entries.begin(), entries.end());
	for(size_t i = 0; i < entries.size() ; ++i){
		auto& currentEntry = entries[i];
		if(currentEntry.guardID == "@"){
			currentEntry.guardID = entries[i-1].guardID;
		}
		if(currentEntry.stat == onDuty){
			if(guards.count(currentEntry.guardID) == 0){
				guards[currentEntry.guardID] = guard(
						currentEntry.guardID);
			}
		}
		auto id = currentEntry.guardID;
		if(guards.count(id) == 0){
			guards[id] = guard(id);
		}
			guard& currentGuard = guards[id];
			if(currentEntry.stat == sleep){
				if(currentGuard.isAsleep){
					std::cout << "Can't make a sleeping" <<
						std::endl;
				}
				currentGuard.isAsleep = true;
				currentGuard.timeFellAsleep = currentEntry.mins;
			}
			if(currentEntry.stat == wake){
				if(!currentGuard.isAsleep){
					std::cout << "Waking up when not asleep" <<
						std::endl;
				}
				currentGuard.isAsleep = false;
				currentGuard.sleepingTime += 
					(currentEntry.mins - 
					 currentGuard.timeFellAsleep);
				currentGuard.timeFellAsleep = 0;
			}
	}

	int mx = 0;
	std::string id = "";
	for(auto& grd : guards){
		if(grd.second.sleepingTime > mx){
			mx = grd.second.sleepingTime;
			id = grd.second.id;
		}
	}
	std::cout << "Most sleeping : " << id << " slept " << mx <<
		std::endl;

	std::map<int, int> numberOfTimesSleeeping;
	guard mostSpleeping(id);
	for(auto& elem : entries){
		if(elem.guardID == id){
			if(elem.stat == sleep){
				mostSpleeping.isAsleep = true;
				mostSpleeping.timeFellAsleep = elem.mins;
			}
			if(elem.stat == wake){
				mostSpleeping.isAsleep = false;
				for(int i = mostSpleeping.timeFellAsleep;
						i < elem.mins;
						++i){
					++numberOfTimesSleeeping[i];
				}
				mostSpleeping.timeFellAsleep = 0;
			}
		}
	}
	int maxMin = 0;
	int maxOcc = 0;
	for(auto& occ : numberOfTimesSleeeping){
		if (occ.second > maxOcc){
			maxMin = occ.first;
			maxOcc = occ.second;
		}
	}
	std::cout << "Slept most on min  : " << maxMin << " (" <<
		maxOcc << ")" << std::endl;
}
