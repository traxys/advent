#include <iostream>
#include <vector> 
#include <fstream>
#include <cmath> 
#include <unordered_map>

struct Point{
	int x;
	int y;
};

namespace std {
		template <> struct hash<Point>{
			size_t operator()(const Point& a) const{
				size_t hsh = 17;
				hsh = hsh * 31 + hash<int>()(a.x);
				hsh = hsh * 31 + hash<int>()(a.y);
				return hsh;
			}
		};
} // namespace std;

bool operator==(const Point& a, const Point& b){
	return a.x == b.x && a.y == b.y;
}

std::istream& operator>>(std::istream& is, Point& obj){
	char voided;
	is >> obj.x >> voided >> obj.y;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& obj){
  os << "[ " << obj.x  <<", "<<obj.y << "]";
  return os;
}

int l1norm(const Point& a, const Point&b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool isOutOfBound(const Point& a,const Point& corner){
	return a.x >= corner.x || a.y >= corner.y || a.x == 0 || a.y == 0;
}

int main(){
	std::ifstream f("inputs/day6");
	Point currentPoint;
	Point corner;
	std::vector<Point> points;
	while(f >> currentPoint){
		points.push_back(currentPoint);
		if(currentPoint.x > corner.x)
			corner.x = currentPoint.x;
		if(currentPoint.y > corner.y)
			corner.y = currentPoint.y;
	}
	corner.x += 10;
	corner.y += 10;
	
	std::unordered_map<Point, std::pair<Point, bool> > closestPoint;
	int regionSize = 0;
	for(int i = 0; i <= corner.x ; ++i){
		for(int j = 0; j <= corner.y ; ++j){
			Point gridPoint;
			gridPoint.x = i;
			gridPoint.y = j;

			Point minP;
			int minDist = 10000;
			bool isTied = false;
			int distanceTotal = 0;
			for(auto& p : points){
				auto dist = l1norm(p, gridPoint);
				distanceTotal += dist;
				if(dist < minDist){
					isTied = false;
					minDist = dist;
					minP = p;
				}else if(dist == minDist){
					isTied = true;
				}
			}
			if( distanceTotal < 10000){
				++regionSize;
			}
			closestPoint[gridPoint] = {minP, isTied};
		}
	}

	std::unordered_map<Point, int> areas;
	for(auto& gp : closestPoint){
		if(!(gp.second.second)){
			auto influentPoint = gp.second.first;
			if( areas[influentPoint] != -1){
				if(isOutOfBound(gp.first, corner)){
					areas[influentPoint] = -1;
				}else{
					++areas[influentPoint];
				}
			}
		}
	}

	int maxArea = 0;
	Point mostInfluentPoint;
	for(auto& area : areas){
		if(area.second > maxArea){
			maxArea = area.second;
			mostInfluentPoint = area.first;
		}
	}

	std::cout << "Most influent : " << mostInfluentPoint << " at " << maxArea << std::endl;
	std::cout << "Safe area : " << regionSize << std::endl;
}
