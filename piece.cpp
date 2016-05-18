/** \file piece.cpp
 *  Implementation of CPiece classes.
 *  \author Oliver Keruľ-Kmec <keruloli@fit.cvut.cz>
 */

#include "piece.h"

CPiece::CPiece(char c){
    m_Colour=c;
}

CPiece::~CPiece(){
    
}

char CPiece::Colour() const{
    return m_Colour;
}

//-------------------------------------------------------------

CKing::CKing(char c): CPiece(c){
    
}

char CKing::Type() const{
    return 'K';
}

bool CKing::ValidMove(int fromCol, int fromRow, int toCol, int toRow, CPiece* const board[8][8]) const{
    if (abs(fromCol-toCol) <= 1 && abs(fromRow - toRow) <= 1){
        return true;
    }

    return false;
}

//-------------------------------------------------------------

CRook::CRook(char c): CPiece(c){
    
}

char CRook::Type() const{
    return 'R';
}

bool CRook::ValidMove(int fromCol, int fromRow, int toCol, int toRow, CPiece* const board[8][8]) const{
    
    // move in a column
    if (fromCol==toCol){
        int rowOffset = toRow > fromRow ? 1 : -1;
        // check squares which are passed
        for (int currRow=fromRow + rowOffset;currRow != toRow; currRow += rowOffset)
            if (board[fromCol][currRow])
                return false;
        return true;
    }

    // move in a row
    else if(fromRow==toRow){
        int colOffset = toCol > fromCol ? 1 : -1;
        // check squares which are passed
        for (int currCol=fromCol + colOffset;currCol != toCol; currCol += colOffset)
            if (board[currCol][fromRow])
                return false;
        return true;
    }

    return false;
}

//-------------------------------------------------------------

CBishop::CBishop(char c): CPiece(c){

}

char CBishop::Type() const{
    return 'B';
}

bool CBishop::ValidMove(int fromCol, int fromRow, int toCol, int toRow, CPiece* const board[8][8])const{
    int colOffset, rowOffset;
    
    if (abs(fromCol-toCol) != abs(fromRow-toRow))
        return false;

    colOffset = toCol > fromCol ? 1 : -1;
    rowOffset = toRow > fromRow ? 1 : -1;
    
    // check squares which are passed
    for (int currRow=fromRow+rowOffset, currCol=fromCol+colOffset;
         currCol != toCol; currRow+=rowOffset, currCol+=colOffset)
        if (board[currCol][currRow])
            return false;
    return true;
}

//-------------------------------------------------------------

CQueen::CQueen(char c): CPiece(c){
    
}

char CQueen::Type() const{
    return 'Q';
}

bool CQueen::ValidMove(int fromCol, int fromRow, int toCol, int toRow, CPiece* const board[8][8])const{

    // move like bishop
    if (abs(fromCol-toCol) == abs(fromRow-toRow)){
        int colOffset = toCol > fromCol ? 1 : -1;
        int rowOffset = toRow > fromRow ? 1 : -1;
        for (int currRow=fromRow+rowOffset, currCol=fromCol+colOffset;
             currCol != toCol; currRow+=rowOffset, currCol+=colOffset)
            if (board[currCol][currRow])
                return false;
        return true;
    }
    
    // move like rook
    else if (fromCol==toCol){
        int rowOffset = toRow > fromRow ? 1 : -1;
        for (int currRow=fromRow + rowOffset;currRow != toRow; currRow += rowOffset)
            if (board[fromCol][currRow])
                return false;
        return true;
    }
    else if(fromRow==toRow){
        int colOffset = toCol > fromCol ? 1 : -1;
        for (int currCol=fromCol + colOffset;currCol != toCol; currCol += colOffset)
            if (board[currCol][fromRow])
                return false;
        return true;
    }
    return false;
}
//-------------------------------------------------------------


CKnight::CKnight(char c): CPiece(c){
    
}

char CKnight::Type() const{
    return 'N';
}

bool CKnight::ValidMove(int fromCol, int fromRow, int toCol, int toRow, CPiece* const board[8][8]) const{
    int colDiff=abs(fromCol-toCol), rowDiff=abs(fromRow-toRow);
    
    if (colDiff==2 && rowDiff==1)
        return true;

    if (colDiff==1 && rowDiff==2)
        return true;

    return false;
}

//-------------------------------------------------------------

CPawn::CPawn(char c): CPiece(c){
    
}

char CPawn::Type() const{
    return 'P';
}

bool CPawn::ValidMove(int fromCol, int fromRow, int toCol, int toRow, CPiece* const board[8][8]) const{
    
    // double move for white
    if (fromRow==1 && !board[fromCol][2] && fromCol==toCol && toRow==3 && !board[toCol][toRow])
        return true;
    
    // double move for black
    if (fromRow==6 && !board[fromCol][5] && fromCol==toCol && toRow==4 && !board[toCol][toRow])
        return true;
    
    // check correct direction
    if (board[fromCol][fromRow]->Colour() == 'W'){
        if (toRow != fromRow+1)
            return false;
    }
    else if (toRow != fromRow-1)
        return false;
    
    // move diagonally if removing other piece
    if (board[toCol][toRow]){
        if (fromCol == toCol+1 || fromCol == toCol-1)
            return true;
    }

    // move forward
    else if (fromCol == toCol)
        return true;

    return false;
}

