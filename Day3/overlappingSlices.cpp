#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using cloth = std::vector< std::vector< int > >;

cloth init(int size){
	cloth newCloth;
	for(int i = 0; i < size; ++i){
		newCloth.push_back(std::vector<int>(size, 0));
	}
	return newCloth;
}

struct Rect{
	std::string id;
	int x;
	int y;
	int heigth;
	int width;
};

int main(){
	std::ifstream f("inputs/day3");
	std::string line;

	auto canvas = init(1000);
	std::vector<Rect> rects;

	while(std::getline(f, line)){
		std::istringstream is(line);
		std::string id;
		char voided;
		int leftPadding, topPadding;
		int heigth, width;
		while( 	is >> 
				id >> 
				voided >> 
				leftPadding >> 
				voided >> 
				topPadding >>
				voided >>
				heigth >>
				voided >>
				width
				){
			rects.push_back({id,
							 topPadding, 
							 leftPadding, 
							 heigth, 
							 width});
		}
	}

	for(auto& rect : rects){
		for(int i = 0; i < rect.heigth; ++i){
			for(int j = 0; j < rect.width; ++j){
				++canvas[i+rect.y][j+rect.x];
			}
		}
	}
	int sum = 0;
	for(auto& line : canvas){
		for(auto& occ : line){
			sum += (occ > 1);
		}
	}
	std::cout << "Sum : " << sum << std::endl;
	
	for(auto& rect : rects){
		bool isOverlapped = false;
		for(int i = 0; i < rect.heigth; ++i){
			for(int j = 0; j < rect.width; ++j){
				if(canvas[i+rect.y][j+rect.x] > 1){
					isOverlapped = true;
					break;
				}
			}
			if(isOverlapped){
				break;
			}
		}
		if(!isOverlapped){
			std::cout << "Not overlapped : " << rect.id 
				<< std::endl;
			break;
		}
	}
}
