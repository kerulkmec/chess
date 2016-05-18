/** \file main.cpp
 *  Main file of project.
 *  \author Oliver Keruľ-Kmec <keruloli@fit.cvut.cz>
 */

/** \mainpage
 *  This project implements chess game.
 *   * It involves all rules including en passant and castling.
 *   * You can save and load a game from a file. You can have saved only one game at the same time.
 *   * Graphics work well only on terminal with black background and white font.
 *  \section sect2 Options:
 *   * A1-A2 - moves a piece from square A1 to square A2
 *   * 0-0 - castling with tke kingside rook
 *   * 0-0-0 - castling with tke queenside rook
 *   * save - saves game to a file
 *   * load - loads game from a file
 *   * exit - quits game
 */

#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, const char * argv[])
{
    CGame game;
    game.Start();
    return 0;
}

