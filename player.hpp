#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
#include <tuple>

using namespace std;

class Player {

public:
    Player(Side s);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    vector<Move*> getPossibleMoves();
    Move *findBestPossibleMove(vector<Move*> possibleMoves);
    int computeScore(Move * aMove);
    
    Side side;
    Side otherSide;
    Board *board;
    vector<Move> mySpaces;
    vector<Move> oppSpace;

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
