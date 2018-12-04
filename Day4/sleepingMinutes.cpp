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
	explicit guard(const std::string& id_) : id(id_), isAsleep(false),
	timeFellAsleep(0), sleepingTime(0) {};
};

int main(){
	std::ifstream f("inputs/day4");
	std::string line;

	std::vector<entry> entries;
	std::map<std::string, guard> guards;
	std::map<int, std::map<std::string, int> > minuteSleptAmount;


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
			currentGuard.isAsleep = true;
			currentGuard.timeFellAsleep = currentEntry.mins;
		}
		if(currentEntry.stat == wake){
			currentGuard.isAsleep = false;
			for(int i = currentGuard.timeFellAsleep;
						i < currentEntry.mins;
						++i){
				++minuteSleptAmount[i][id];
			}
			currentGuard.timeFellAsleep = 0;
		}
	}
	int maxMin = 0;
	int maxOcc = 0;
	std::string maxId;
	for(auto& minute : minuteSleptAmount){
		for(auto& guardAmount : minute.second){
			if(maxOcc < guardAmount.second){
				maxMin = minute.first;
				maxOcc = guardAmount.second;
				maxId = guardAmount.first;
			}
		}
	}

	std::cout << "Guard "<< maxId << " slept "<< maxOcc << " times on minute "<< maxMin << std::endl;
}
