#include <iostream>
#include <iomanip>
#include <vector>

class Powergrid{
	public:
		void print() const {
			for(auto& row : grid){
				for(auto& cell : row){
					std::cout << std::setw(2) << cell;
				}
				std::cout << std::endl;
			}
		}
		explicit Powergrid(int gridId) : id(gridId) {
			grid.resize(300, std::vector<int>(300, 0));
			for(int x = 0; x < 300 ; ++x){
				for(int y = 0; y < 300; ++y){
					int rackID = (x + 1) + 10;
					grid[x][y] = (rackID*rackID*(y+1) + rackID*id)/100 % 10 - 5;
				}
			}
			partialSums.resize(300, std::vector<int>(300, 0));
			for(int x = 0; x < 300; ++x){
				partialSums[x][0] = grid[x][0];
				for(int y = 1; y < 300; ++y){
					partialSums[x][y] = partialSums[x][y-1] + grid[x][y];
				}
			}
		}
		int convolute(int topx,int topy, int size) const {
			int sum = 0;
			for(int x = 0; x < size; ++x){
				if(topy == 0){
					sum += partialSums[topx+x][size-1];
				}
				else{
					sum += partialSums[topx+x][topy+size-1] - partialSums[topx+x][topy-1];
				}
			}
			return sum;
		}
		std::pair<int,int> bestPowerSize(int size) const{
			int bestX = -1;
			int bestY = -1;
			int maxPower = -0xfffff;
			for(int x = 0; x < 300 - size; ++x){
				for(int y = 0; y < 300 - size; ++y){
					auto currentPower = convolute(x,y, size);
					if(currentPower > maxPower){
						maxPower = currentPower;
						bestX = x;
						bestY = y;
					}
				}
			}
			return {bestX, bestY};
		}
		std::pair<std::pair<int,int>, int> bestPower() const{
			std::pair<int,int> bestCoord = {-1, -1};
			int bestSize = -1;
			int maxPower = 0;
			for(int size = 1; size <= 299; ++size){
				std::cout << size << std::endl;
				auto powerCoords = bestPowerSize(size);
				int powerLevel = convolute(powerCoords.first, powerCoords.second, size);
				if(powerLevel > maxPower){
					maxPower = powerLevel;
					bestSize = size;
					bestCoord = powerCoords;
				}
			}
			return {bestCoord, bestSize};
		}
	private:
		std::vector< std::vector<int> > grid;
		std::vector< std::vector<int> > partialSums;
		int id;
};

int main(){
	int input = 3031;
	Powergrid grid(input);
	auto maxPower = grid.bestPowerSize(3);
	std::cout << "Max power for size 3 is : " << grid.convolute(maxPower.first, maxPower.second, 3)
		<< " at " << maxPower.first + 1 << "," << maxPower.second + 1 << std::endl;
	auto anySize = grid.bestPower();
	std::cout << "Max power is " << grid.convolute(anySize.first.first, anySize.first.second, anySize.second)
		<< " at " << anySize.first.first << "," << anySize.first.second << " with size of " << anySize.second << std::endl;
}
