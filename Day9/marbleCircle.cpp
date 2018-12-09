#include <iostream>
#include <fstream>
#include <list>
#include <map>

enum rotationSide {clockwise, counterClockwise};

class MarbleCircle{
	public:
		MarbleCircle(size_t numberOfPlayers,int64_t largestMarble_) :
			marbles({0}),
			current(marbles.begin()),
			largestMarble(largestMarble_),
			playerCount(numberOfPlayers),
			currentPlayer(0) {}

		void move(size_t dist, rotationSide side){
			if(side == clockwise){
				for(size_t i = 0; i < dist; ++i){
					++current;
					if(current == marbles.end())
						current = marbles.begin();
				}
			}
			else{
				for(size_t i = 0; i < dist; ++i){
					if(current == marbles.begin())
						current = marbles.end();
					--current;
				}
			}
		}

		bool play(int64_t marble){
			if(marble % 23 == 0){
				scores[currentPlayer] += marble;
				move(7, counterClockwise);
				scores[currentPlayer] += (*current);
				current = marbles.erase(current);
			}
			else{
				move(1, clockwise);
				current++;
				current = marbles.insert(current, marble);
			}
			currentPlayer = (currentPlayer + 1) % playerCount;
			return marble != largestMarble;
		};

		void print(){
			//std::cout << "[" << currentPlayer << "] ";
			for(auto& marble : marbles){
				if(marble == (*current)){
					std::cout << "(" << marble << ") ";
				}else{
					std::cout << marble << " ";
				}
			}
			std::cout << std::endl;
		}

		std::pair<int, int64_t> highscore() const{
			std::pair<int, int64_t> maxPair = {-1, -1};
			for(auto& player : scores){
				if(player.second > maxPair.second){
					maxPair = player;
				}
			}
			return maxPair;
		}
		int64_t scoreOf(int player) const{
			return scores.at(player);
		}
	private:
		std::list<int64_t> marbles;
		std::list<int64_t>::iterator current;
		
		int64_t largestMarble;
		
		std::map<int, int64_t> scores;
		size_t playerCount;
		size_t currentPlayer;
};

int main(){
	std::ifstream f("inputs/day9");
	std::string voided;
	int64_t maxMarble;
	int players;
	f >> players >> voided >> voided >> voided >> voided >> voided
		>> maxMarble;

	MarbleCircle game(players, maxMarble);
	int64_t marbleNum = 1;
	while(game.play(marbleNum)){
		//game.print();
		++marbleNum;
	}
	auto bestScore = game.highscore();
	std::cout << "Best score is : " << bestScore.second
		<< " for player " << bestScore.first << std::endl;
	
	MarbleCircle gameLong(players, maxMarble*100);
	int64_t marbleNumLong = 1;
	while(gameLong.play(marbleNumLong)){
		//game.print();
		++marbleNumLong;
	}
	auto bestScoreLong = gameLong.highscore();
	std::cout << "Best score (long game) is : " 
		<< bestScoreLong.second
		<< " for player " << bestScoreLong.first << std::endl;
}
