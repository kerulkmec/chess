/** \file piece.h
 *  Header for CPiece classes.
 *  \author Oliver Keruľ-Kmec <keruloli@fit.cvut.cz>
 */

#ifndef __chess__CPiece__
#define __chess__CPiece__

#include <iostream>
#include <cmath>

using namespace std;

/// Chess piece
/**
 This abstract class represents one chess piece.
 It stores its colour.
 */
class CPiece{
public:
    /// Constructor
    /**
     Creates new piece of given colour.
     \param colour colour of piece
    */
    CPiece(char colour);
    /// Destructor
    virtual ~CPiece();
    /// Returns type of piece
    virtual char Type() const=0;
    /// Returns colour of piece
    /**
     \return 'W' for white piece
     \return 'B' for black piece
     */
    char Colour() const;
    /// Checks if piece can move to given position.
    /**
     \param fromCol column of starting positon
     \param fromRow row of starting position
     \param toCol column of destination position
     \param toRow row of destination position
     \param board 2D 8x8 array of pieces
     \return true if move is valid
     \return false if move is not valid
     */
    virtual bool ValidMove(int fromCol, int fromRow, int toCol, int toRow, CPiece* const board[8][8])  const=0;
protected:
    /// Colour of piece
    char m_Colour;
};

/// King
/**
 This class represents one king.
 It stores its colour.
 */
class CKing: public CPiece{
public:
    /// Constructor
    /**
     Creates new king of given colour.
     \param colour colour of piece
     */
    CKing(char colour);
    /// Returns type of piece
    /**
     \return 'K'
     */
    char Type() const;
    bool ValidMove(int, int, int, int, CPiece* const [8][8]) const;
};

/// Rook
/**
 This class represents one rook.
 It stores its colour.
 */
class CRook: public CPiece{
public:
    /// Constructor
    /**
     Creates new rook of given colour.
     \param colour colour of piece
     */
    CRook(char colour);
    /// Returns type of piece
    /**
     \return 'R'
     */
    char Type() const;
    bool ValidMove(int, int, int, int, CPiece* const[8][8]) const;
};

/// Bishop
/**
 This class represents one bishop.
 It stores its colour.
 */
class CBishop: public CPiece{
public:
    /// Constructor
    /**
     Creates new bishop of given colour.
     \param colour colour of piece
     */
    CBishop(char colour);
    /// Returns type of piece
    /**
     \return 'B'
     */
    char Type() const;
    bool ValidMove(int, int, int, int, CPiece* const [8][8]) const;
};

/// Queen
/**
 This class represents one queen.
 It stores its colour.
 */
class CQueen: public CPiece{
public:
    /// Constructor
    /**
     Creates new queen of given colour.
     \param colour colour of piece
     */
    CQueen(char colour);
    /// Returns type of piece
    /**
     \return 'Q'
     */
    char Type() const;
    bool ValidMove(int, int, int, int, CPiece* const [8][8]) const;
};

/// Pawn
/**
 This class represents one pawn.
 It stores its colour.
 */
class CPawn: public CPiece{
public:
    /// Constructor
    /**
     Creates new pawn of given colour.
     \param colour colour of piece
     */
    CPawn(char colour);
    /// Returns type of piece
    /**
     \return 'P'
     */
    char Type() const;
    bool ValidMove(int, int, int, int, CPiece* const [8][8]) const;
};

/// Knight
/**
 This class represents one knight.
 It stores its colour.
 */
class CKnight: public CPiece{
public:
    /// Constructor
    /**
     Creates new knight of given colour.
     \param colour colour of piece
     */
    CKnight(char colour);
    /// Returns type of piece
    /**
     \return 'N'
     */
    char Type() const;
    bool ValidMove(int, int, int, int, CPiece* const [8][8]) const;
};

#endif /* defined(__chess__CPiece__) */

