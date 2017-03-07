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
    
    if (this->side == WHITE) {
        this->otherSide = BLACK;    
    }
    else {
        this->otherSide = WHITE;
    }
    
    this->board = new Board();
    this->side = s;
    
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
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
    int size = possibleMoves.size();
    if (size == 0) {
       return nullptr;
    }
    //srand (time(NULL));
    //int randomNum = rand() % size;
    this->board->doMove(possibleMoves[0], side);     
    Move *chosen = possibleMoves[0];
    cerr<<"Move chosen: "<<chosen->getX()<<" "<<chosen->getY()<<"\n";

    return possibleMoves[0];
}

//Updates the board to reflect the change in the move
void Player::updateBoard(Move *ourMove) {
   board->doMove(ourMove, side);
   //Make a for loop to change our board
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
                cerr<<"passed "<<m->getX()<<" "<<m->getY()<<"\n";
                possible.push_back(m);
            }
            else {
                cerr<<"!pass "<<m->getX()<<" "<<m->getY()<<"\n";
            }
        }
    }
    cerr<<"Possible moves: \n";
    for (int i = 0; i < possible.size(); i++) {
       cerr<<possible[i]->getX()<<" "<<possible[i]->getY()<<"\n";
    }

    return possible;
}
