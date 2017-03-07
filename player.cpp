#include "player.hpp"
#include <vector>

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
    this->board->set;
    this->side = s;
    this->otherSide = os;
    
    //Get the starting pieces and put them into our vectors  
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
           if (board.get(s, row, col)) {
              Move myMove = new Move(row, col);
              this.mySpaces.push_back(myMove);
           }
           else if (board.get(os, row, col)) {
              Move oppMove = new Move(row, col);
              this.oppSpace.push_back(oppMove);
           }
        }
    }
    
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
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    this->board->doMove(opponentsMove, otherSide);
    this->oppSpace.push_back(opponetsMove);
        

        

    return nullptr;
}

//The point of this function is to get all of the possible moves. We are going
//to do this by iterating through all of the spaces we own and then seeing if 
//there's a space of the opposite color near it
Vector<Move> *Player::getPossibleMoves() {
    int xCor = 0;
    int yCor = 0;
    Vector<Moves> possible;
    for (int i = 0; i < this.mySpaces.size(); i++) {
        xCor = this.mySpaces[i].getX();
        yCor = this.mySpaces[i].getY();
          
 
    }

//Use this function to explore immediate 8 squares around our central one
//try to find square of opposite color        
Vector<Move> *Player::branch(int x, int y) {
   




