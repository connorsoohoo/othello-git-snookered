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

    this->board->doMove(opponentsMove, this->otherSide);
    vector<Move*> possibleMoves = getPossibleMoves(this->board, this->side);      
    unsigned int size = possibleMoves.size();
    if (size == 0) {
       return nullptr;
    }
    if (this->board->isDone())
    {
		return nullptr;
	}

	Move *chosen = this->findBestPossibleMove(possibleMoves, side, true);
	this->board->doMove(chosen, side);
	return chosen;
}

// Finds and returns the move with the best heuristic score
Move * Player::findBestPossibleMove(vector <Move*> possibleMoves, Side s, bool iter) {
   
   // create vector with indices that correspond to the move index
   vector <int> scores;
   
   int bestScore = -100;
   int bestScoreIndex = 0;
   for (unsigned int i = 0; i < possibleMoves.size(); i++)
   {
	   Move *aMove = possibleMoves.at(i);
	   Board *theBoard = this->board->copy();
	   scores.push_back(this->computeScore(aMove, theBoard, 0, s, iter));
	   if (scores.at(i) > bestScore)
	   {
		   bestScoreIndex = i;
		   bestScore = scores.at(i);
	   }
   }
   
   return possibleMoves.at(bestScoreIndex);
}

// Computes the heuristic score for a given move
int Player::computeScore(Move *aMove, Board *theBoard, int total, Side s, bool iter)
{
	Side nextS = this->side;
	bool mySide = false;
	if (s == this->side) {
		mySide = true;
		nextS = this->otherSide;
	}
	
	// iterate in all 8 directions to get the total
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			total += this->addScoreInDirection(aMove, x, y, mySide);
		}
	}
	
	// Check end cases of recursion
	vector<Move *> possibleMoves = this->getPossibleMoves(theBoard, this->otherSide);
	if (possibleMoves.size() == 0) {
       return total;
    }
    if (this->board->isDone())
    {
		return total;
	}
	// now compute how many spaces opponent will take back by copying 
	// and simulating moves recursively (1-depth) on a test board 
	if (iter) {
		Move *chosen = this->findBestPossibleMove(possibleMoves, nextS, false);
		theBoard->doMove(chosen, nextS);
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				total -= this->addScoreInDirection(chosen, x, y, !mySide);
			}
		}
	}
	
	// apply bonuses for corners, edges, and penalties 
	if (this->isCornerMove(aMove))
	{
		total += 7;
	}/* 
	else if (this->isBadMove(aMove))
	{
		total -= 0;
	} else if (this->isEdge(aMove)) {
		total += 3;
	}
	*/
	return total;
}

// adds the score to the heuristic for one direction of searching
int Player::addScoreInDirection(Move *aMove, int dx, int dy, bool mySide)
{
	Side oppSide = this->side;
	if (mySide) {
		oppSide = this->otherSide;
	}
	
	int dirTotal = 0;
	int x = aMove->getX();
	int y = aMove->getY();
	
	x += dx;
	y += dy;
	while (this->board->onBoard(x, y) && this->board->get(oppSide, x, y)) {
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

// Checks if the Move is a corner 
bool Player::isCornerMove(Move *aMove)
{
	int x = aMove->getX();
	int y = aMove->getY();
	if ((x == 0) || (x == 7))
	{
		if ((y == 0) || (y == 7))
		{
			return true;
		}
	}
	return false;
}

// Checks if the Move is an edge 
bool Player::isEdge(Move *aMove)
{
	int x = aMove->getX();
	int y = aMove->getY();
	if ((x == 0) || (x == 7) || (y == 0) || (y == 7))
	{
		return true;
	}
	return false;
}

// Checks if the Move is a bad move, in this case defined
// as one away from the corners and edges
bool Player::isBadMove(Move *aMove)
{
	int x = aMove->getX();
	int y = aMove->getY();
	if ((x == 1) || (x == 6))
	{
		if ((y == 1) || (y == 6))
		{
			return true;
		}
	}
	return false;
}

/*
 * This function goes though all of the points on the board and sees if a 
 * move can be placed there.
 */
vector<Move*> Player::getPossibleMoves(Board *theBoard, Side s) {
    vector<Move*> possible;
    for (int row = 0; row < 8; row++) {
       for (int col = 0; col < 8; col++) {
            Move *m = new Move(row, col);
            bool poss = theBoard->checkMove(m, s);
            if (poss) {
                possible.push_back(m);
            }
        }
    }
    return possible;
}
