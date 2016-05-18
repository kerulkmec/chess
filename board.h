/** \file board.h
 *  Header for CBoard class.
 *  \author Oliver Keruľ-Kmec <keruloli@fit.cvut.cz>
 */

#ifndef __chess__CBoard__
#define __chess__CBoard__

#include <iostream>
#include <cctype>
#include <fstream>
#include "piece.h"

using namespace std;

/// Game board
/**
 It represents a game board.
 It stores array of pieces, information about en passant position and information if castling is possible.
 */
class CBoard{
public:
    /// Constructor
    /**
     Creates all pieces on their starting positions.
     */
    CBoard();
    /// Destructor
    ~CBoard();
    /// Prints the board and options menu.
    /**
     Works well only on terminal with black background and white font.
     */
    void Print() const;
    /// Moves a piece if possible.
    /**
     \param move string from user in format A1-A2
     \param player player on turn
     \return 1 move was valid
     \return 2 chosen squares out of board
     \return 3 chosen opponent's piece
     \return 4 destination square occupied by player's piece
     \return 5 invalid move for piece
     \return 6 move into check
     \return 7 impossible castling because of moved king or rook
     \return 8 impossible castling because of piece between king and rook
     \return 9 impossible castling because of check
     */
    int Move(const string & move, char player);
    /// Checks if player is in check.
    /**
     \param player checked player
     \return true if player is in check
     \return false if player is not in check
     */
    bool inCheck(char player) const;
    /// Checks if player can make valid move.
    /**
     \param player checked player
     \return true if player can move
     \return false if player can't move
     */
    bool canMove(char player);
    /// Saves board to output file stream
    /**
     Saves all board information to file stream in format for Load method.
     \param stream output file stream
     */
    void Save(ofstream & stream) const;
    /// Loads board from input file stream
    /**
     Loads board in format made by Save method.
     \param stream input file stream
     */
    void Load(ifstream & stream);
private:
    int castling(int, int, char);
    bool promotion(int, int, char);
    CPiece* board[8][8];
    int enp[2];
    int cast[4];
};

#endif /* defined(__chess__CBoard__) */
