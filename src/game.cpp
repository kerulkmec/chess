/** \file game.cpp
 *  Implementation of CGame class.
 *  \author Oliver Keruľ-Kmec <keruloli@fit.cvut.cz>
 */

#include "game.h"

CGame::CGame():turn('W'){
    
}

void CGame::Start(){
    string move;
    do {
        board.Print();
        cout<<"Choose your move or another option. ";

        if (board.inCheck(turn))
            cout<<"You're in check! ";

        cout<<turn<<"'s turn: ";
        cin>>move;
        
        // check options
        if (move=="exit")
            break;
        if (move=="save"){
            if (Save())
                cout<<"Your game was saved."<<endl;
            else
                cout<<"Not possible to save game."<<endl;
            continue;
        }
        if (move=="load"){
            if (Load())
                cout<<"Your game was loaded from a file."<<endl;
            else
                cout<<"Not possible to load game."<<endl;
            continue;
        }

        switch (board.Move(move,turn)) {
            case 1:
                turn = turn=='B'?'W':'B';
                break;
            case 2:
                cout<<"Invalid squares."<<endl;
                break;
            case 3:
                cout<<"Chosen piece is not yours."<<endl;
                break;
            case 4:
                cout<<"Destination square is occupied by your piece."<<endl;
                break;
            case 5:
                cout<<"Invalid move for piece."<<endl;
                break;
            case 6:
                cout<<"You can't move into check."<<endl;
                break;
            case 7:
                cout<<"Castling not possible. Rook or king was moved."<<endl;
                break;
            case 8:
                cout<<"There is a piece between king and rook."<<endl;
                break;
            case 9:
                cout<<"You are or would be in check while moving."<<endl;
                break;
        }
    } while (!isEnd());
}

bool CGame::isEnd() {

    // check if player can move
    if (!board.canMove(turn)){
        // if in check - checkmate
        if (board.inCheck(turn)){
            board.Print();
            cout<<"Checkmate! "<<(turn=='W'?"Black player wins":"White player wins")<<endl;
            return true;
        }
        // if not in check - stalemate
        else{
            board.Print();
            cout<<"Stalemate!"<<endl;
            return true;
        }
    }
    return false;
}

bool CGame::Save() const{
    ofstream f(SAVEFILE,ofstream::out);

    if (f.fail()) 
        return false;
    
    board.Save(f);
    f<<turn;
    f<<endl;
    return true;
}

bool CGame::Load(){
    ifstream f(SAVEFILE,ifstream::in);

    if (f.fail()) 
        return false;

    board.Load(f);
    f>>turn;
    return true;
}
