#include "player.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side s) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = s;
   
    if (this->side == WHITE) {
        this->otherSide = BLACK;    
    }
    else {
        this->otherSide = WHITE;
    }
    
    this->board = new Board();
    
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {

    this->board->doMove(opponentsMove, otherSide);
    vector<Move*> possibleMoves = getPossibleMoves();      
    unsigned int size = possibleMoves.size();
    if (size == 0) {
       return nullptr;
    }
    if (this->board->isDone())
    {
		return nullptr;
	}
    //srand (time(NULL));
    //int randomNum = rand() % size;
    //this->board->doMove(possibleMoves[0], side);     
    //Move *chosen = possibleMoves[0];
    //cerr<<"Move chosen: "<<chosen->getX()<<" "<<chosen->getY()<<"\n";

/*
    int randomNum = rand() % size;
    this->board->doMove(possibleMoves[randomNum], side);     
    Move *chosen = possibleMoves[randomNum];
    return possibleMoves[randomNum];
*/
	Move *chosen = this->findBestPossibleMove(possibleMoves);
	this->board->doMove(chosen, side);
	return chosen;
}

// Finds and returns the move with the best heuristic score
Move * Player::findBestPossibleMove(vector <Move*> possibleMoves) {
   
   // create vector with indices that correspond to the move index
   vector <int> scores;
   
   int bestScore = 0;
   int bestScoreIndex = 0;
   for (unsigned int i = 0; i < possibleMoves.size(); i++)
   {
	   Move *aMove = possibleMoves.at(i);
	   scores.push_back(this->computeScore(aMove));
	   if (scores.at(i) > bestScore)
	   {
		   bestScoreIndex = i;
		   bestScore = scores.at(i);
	   }
   }
   
   return possibleMoves.at(bestScoreIndex);
}

// Computes the heuristic score for a given move
int Player::computeScore(Move *aMove)
{
	// iterate in all 8 directions to get the total
	int total = 0;
	
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			total += this->addScoreInDirection(aMove, x, y);
		}
	}
	
	return total;
}

// adds the score to the heuristic for one direction of searching
int Player::addScoreInDirection(Move *aMove, int dx, int dy)
{
	int dirTotal = 0;
	int x = aMove->getX();
	int y = aMove->getY();
	
	x += dx;
	y += dy;
	while (this->board->onBoard(x, y) && this->board->get(this->otherSide, x, y)) {
		dirTotal += 1;
		x += dx;
		y += dy;
	}
	// If not on the board after iteration, means other has taken over row
	if (!this->board->onBoard(x, y))
	{
		dirTotal = 0;
	}
	
	return dirTotal;
}

/*
 * This function goes though all of the points on the board and sees if a 
 * move can be placed there.
 */
vector<Move*> Player::getPossibleMoves() {
    vector<Move*> possible;
    for (int row = 0; row < 8; row++) {
       for (int col = 0; col < 8; col++) {
            Move *m = new Move(row, col);
            bool poss = this->board->checkMove(m, side);
            if (poss) {
                possible.push_back(m);
            }
        }
    }/*
    cerr<<"Possible moves: \n";
    for (unsigned int i = 0; i < possible.size(); i++) {
       cerr<<possible[i]->getX()<<" "<<possible[i]->getY()<<"\n";
    }
	*/
    return possible;
}
