#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

struct Cart{
	uint64_t x;
	uint64_t y;
	int direction;
	int intersectionCount;
	
	void move(const std::vector<std::string>& grid){
		if(direction == 0)
			--x;
		if(direction == 1)
			--y;
		if(direction == 2)
			++x;
		if(direction == 3)
			++y;
		char currentRail = grid[x][y];
		if(currentRail == '+'){
			direction += intersectionCount;
			if(direction > 3)
				direction -= 4;
			if(direction < 0){
				direction += 4;
			}
			if(intersectionCount == 1)
				intersectionCount = 0;
			else if(intersectionCount == 0)
				intersectionCount = -1;
			else if(intersectionCount == -1)
				intersectionCount = 1;
		}
		if(currentRail == '\\'){
			if(direction == 1)
				direction = 0;
			else if(direction == 0)
				direction = 1;
			else if(direction == 2)
				direction = 3;
			else if(direction == 3)
				direction = 2;
		}
		if(currentRail == '/'){
			if(direction == 1)
				direction = 2;
			else if(direction == 2)
				direction = 1;
			else if(direction == 0)
				direction = 3;
			else if(direction == 3)
				direction = 0;
		}
	}
};

namespace std {
		template <> struct hash<Cart>{
			size_t operator()(const Cart& a) const{
				size_t hsh = 17;
				hsh = hsh * 31 + hash<uint64_t>()(a.x);
				hsh = hsh * 31 + hash<uint64_t>()(a.y);
				hsh = hsh * 31 + hash<int>()(a.direction);
				return hsh;
			}
		};
} // namespace std;

inline bool operator<(const Cart& c1, const Cart& c2){
	if( c1.x == c2.x ){
		if( c1.y == c2.y){
			return c1.direction < c2.direction;
		}
		return c1.y < c2.y;
	}	
	return c1.x < c2.x;
}

void printGrid(const std::vector<std::string>& grid,
			   const std::vector<Cart>& carts){
	std::vector<std::string> gridCopy = grid;
	for(auto& cart: carts){
		char cartRepr = 'C';
		if(cart.direction == 0){
			cartRepr = '^';
		}
		if(cart.direction == 1){
			cartRepr = '<';
		}
		if(cart.direction == 2){
			cartRepr = 'v';
		}
		if(cart.direction == 3){
			cartRepr = '>';
		}
		gridCopy[cart.x][cart.y] = cartRepr;
	}
	for(auto& line : gridCopy){
		std::cout << line << std::endl;
	}
}

bool collision(const std::vector<Cart>& carts,
		       std::pair<uint64_t,uint64_t>& coords){
	for (auto i = carts.begin(); i != carts.end(); ++i) {
  		for (auto j = i; ++j != carts.end(); /**/) {
			if( i->x == j->x && i->y == j->y){
				coords.first = i->x;
				coords.second = i->y;
				return true;
			}
		}
	}
	return false;
}

int main(){
	std::ifstream f("inputs/day13");
	std::string line;
	std::vector<std::string> grid;
	std::vector<Cart> carts;
	uint64_t x = 0;
	while(std::getline(f, line)){
		for(uint64_t y = 0; y < line.size(); ++y){
			if(line[y] == '^'){
				carts.push_back({x,y,0,1});
				line[y] = '|';
			}
			if(line[y] == 'v'){
				carts.push_back({x,y,2,1});
				line[y] = '|';
			}
			if(line[y] == '>'){
				carts.push_back({x,y,3,1});
				line[y] = '-';
			}
			if(line[y] == '<'){
				carts.push_back({x,y,1,1});
				line[y] = '-';
			}
		}
		grid.push_back(line);
		++x;
	}
	bool firstCrash = true;
	//printGrid(grid, carts);
	std::pair<uint64_t,uint64_t> crash = {0,0};
	while(true){
		for(auto& cart : carts){
			cart.move(grid);
			if(collision(carts, crash)){
				if(firstCrash){
					std::cout << "Crash at : " << crash.second 
						<< "," << crash.first << std::endl;
					firstCrash = false;
				}
				auto elem1 = 
					std::find_if(carts.begin(), carts.end(),
							[&crash](const Cart& c){
								return c.x == crash.first &&
									   c.y == crash.second;
							});
				carts.erase(elem1);
				auto elem2 = 
					std::find_if(carts.begin(), carts.end(),
							[&crash](const Cart& c){
								return c.x == crash.first &&
									   c.y == crash.second;
							});
				carts.erase(elem2);
			}
		}
		if(carts.size() == 1)
			break;
		std::sort(carts.begin(), carts.end());
		//printGrid(grid, carts);
	}
	std::cout << carts.size() << std::endl;
	carts[0].move(grid);
	std::cout << "Last cart is at : " << carts[0].y << "," <<
		carts[0].x << std::endl;
}
