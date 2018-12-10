#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <chrono>
#include <thread>
#include <vector>

struct Point{
	int x;
	int y;
	int id;

	void move(const Point& vel){
	 	x += vel.x;
		y += vel.y;
	}

	Point() : x(0), y(0), id(-1) {}
	Point(int x_, int y_, int id_) : x(x_), y(y_), id(id_) {}
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

bool operator<(const Point& a, const Point& b){
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

std::ostream& operator<<(std::ostream& os,const Point& p){
		os << "<" << p.x << "," << p.y << ">";
		return os;
}

std::pair<Point,Point> box(const std::vector<Point>& points){
	Point topL = *(points.begin());
	Point botR = *(points.begin());
	for(auto& p : points){
		if(p.x < topL.x)
			topL.x = p.x;
		if(p.y > topL.y)
			topL.y = p.y;
		if(p.x > botR.x)
			botR.x = p.x;
		if(p.y < botR.y)
			botR.y = p.y;
	}
	return {topL, botR};
}

uint64_t boxArea(const std::pair<Point,Point>& bx){
	return (bx.second.x - bx.first.x) * (bx.first.y - bx.second.y);
}

void printPoints(const std::vector<Point>& points){
	auto corners = box(points);
	std::set<Point> noidpts;
	for(auto& p : points){
		noidpts.insert(Point(p.x, p.y, 0));
	}
	for(int y = corners.second.y; y <= corners.first.y; y++){
		for(int x = corners.first.x; x <= corners.second.x; x++){
			if(noidpts.count(Point(x,y,0)) == 1){
				std::cout << "#";
			}else{
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}
}

int main(){
	std::vector<Point> points;
	std::map<int, Point> velocities;

	std::ifstream f("inputs/day10");
	std::string voided;
	int x, y, px, py;
	f.ignore(10);
	int i = 0;
	while(f >> x >> voided >> y >> voided){
		f.ignore(11);
		f >> px >> voided >> py >> voided;
		Point p(x,y,i);
		Point vel(px,py, i);
		velocities[i] = vel;
		points.push_back(p);
		f.ignore(11);
		++i;
	}
	uint64_t t = 1;
	uint64_t oldArea = 0xffffffffffffffff;
	while(true){
		std::vector<Point> newPoints(points);
		for(auto& p : newPoints){
			p.move(velocities.at(p.id));
		}
		auto corners = box(newPoints);
		uint64_t newArea = boxArea(corners);
		if(newArea > oldArea && (corners.second.x - corners.first.x) < 300){
			std::cout << "At t = "<< t << std::endl;
			printPoints(points);
			break;
		}else{
			points = newPoints;
			oldArea = newArea;
		}
		++t;
	}
}
