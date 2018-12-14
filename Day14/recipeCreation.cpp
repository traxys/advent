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
	uint64_t input = 556061;
	std::string recipeBoard = "37";
	std::vector<Elf> elves;
	elves.push_back(Elf(0,recipeBoard));
	elves.push_back(Elf(1,recipeBoard));
	while(recipeBoard.size() < input + 10){
		//printBoard(elves);
		int sum = 0;
		for(auto& elf : elves){
			sum += elf.getValue();
		}
		recipeBoard += std::to_string(sum);
		for(auto& elf : elves){
			elf.recipeIndex += 1 + elf.getValue();
			elf.recipeIndex %= recipeBoard.size();
		}
	}
	std::cout << recipeBoard.substr(input,10) << std::endl;
	return 0;
}
