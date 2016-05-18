/** \file game.h
 *  Header for CGame class.
 *  \author Oliver Keruľ-Kmec <keruloli@fit.cvut.cz> 
 */

#ifndef __chess__CGame__
#define __chess__CGame__

#include <iostream>
#include <fstream>
#include "board.h"

#define SAVEFILE  "save"

/// Chess game
/**
 This class represents concrete chess game.
 It stores CBoard class as board of pieces and information who is on turn.
 */
class CGame{
public:
    /// Constructor
    /**
     Set that first player on turn is white player.
     */
    CGame();
    /// Starts a new game
    /** 
     Game runs in this method.
     It controls game and interact with user.
     */
    void Start();
private:
    bool Save() const;
    bool Load();
    bool isEnd();
    char turn;
    CBoard board;
};

#endif /* defined(__chess__CGame__) */

