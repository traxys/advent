#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

struct Elf{
	uint64_t recipeIndex;
	const std::string& board;

	Elf(uint64_t initialRecipe,const std::string& board_)
		:	recipeIndex(initialRecipe),
			board(board_) {}

	int getValue() const{
		return board[recipeIndex] - 48;
	}
};

void printBoard(const std::vector<Elf>& elves){
	std::set<uint64_t> elvesIndex;
	for(auto& elf : elves){
		elvesIndex.insert(elf.recipeIndex);
	}
	for(size_t i = 0; i < elves[0].board.size(); ++i){
		if(elvesIndex.count(i) == 1){
			std::cout << "(" << elves[0].board[i] << ")";
		}else{
			std::cout << elves[0].board[i];
		}
	}
	std::cout << std::endl;
}

int main(){
	std::string input = "556061";
	std::string recipeBoard = "37";
	std::vector<Elf> elves;
	elves.push_back(Elf(0,recipeBoard));
	elves.push_back(Elf(1,recipeBoard));
	uint64_t lastStartIndex = 0;
	bool seenStart = false;
	while(true){
		//if(recipeBoard.size() % 1000 == 0)
		//	std::cout << recipeBoard.size() << " looking after : " << lastStartIndex << std::endl; 
		int sum = 0;
		for(auto& elf : elves){
			sum += elf.getValue();
		}
		recipeBoard += std::to_string(sum);
		for(auto& elf : elves){
			elf.recipeIndex += 1 + elf.getValue();
			elf.recipeIndex %= recipeBoard.size();
		}
		if(!seenStart){

			if(recipeBoard.find(input[0]) != 
					std::string::npos){
				seenStart = true;
				lastStartIndex = recipeBoard.find(input[0]);
			}
		}
		if(seenStart){
			if(recipeBoard.find(input, lastStartIndex) != std::string::npos){
				break;
			}
			else if(recipeBoard.size() - lastStartIndex >= input.size()){
				if(recipeBoard.find(input[0], lastStartIndex + 1) != std::string::npos){
					lastStartIndex = recipeBoard.find(input[0], lastStartIndex + 1);
				}
			}
		}
	}
	auto index = recipeBoard.find(input);
	std::cout << "Patern at : " << index << std::endl; 
	//std::cout << recipeBoard.size() - input.size() << std::endl;
	return 0;
}
