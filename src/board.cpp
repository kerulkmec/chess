/** \file board.cpp
 *  Implementation of CBoard class.
 *  \author Oliver Keruľ-Kmec <keruloli@fit.cvut.cz>
 */

#include "board.h"

CBoard::CBoard(){

    // create pawns
    for (int i=0;i<8;++i){
        board[i][1] = new CPawn('W');
        board[i][6] = new CPawn('B');
    }
    
    // create other pieces
    board[0][0] = new CRook('W');
    board[7][0] = new CRook('W');
    board[1][0] = new CKnight('W');
    board[6][0] = new CKnight('W');
    board[2][0] = new CBishop('W');
    board[5][0] = new CBishop('W');
    board[3][0] = new CQueen('W');
    board[4][0] = new CKing('W');
    board[0][7] = new CRook('B');
    board[7][7] = new CRook('B');
    board[1][7] = new CKnight('B');
    board[6][7] = new CKnight('B');
    board[2][7] = new CBishop('B');
    board[5][7] = new CBishop('B');
    board[3][7] = new CQueen('B');
    board[4][7] = new CKing('B');
    
    // NULL other squares
    for (int i=0;i<8;++i)
        for (int j=2;j<6;++j)
            board[i][j]=NULL;
    
    enp[0]=enp[1]=8;
    cast[0]=cast[1]=cast[2]=cast[3]=1;
}

CBoard::~CBoard(){
    for (int i=0;i<8;++i)
        for (int j=0;j<8;++j)
            delete board[i][j];
}

void CBoard::Print() const{
    cout<<endl;
    cout<<"     A    B    C    D    E    F    G    H "<<endl;
    cout<<"   ---------------------------------------"<<endl;

    for (int i=7;i>=0;--i){
        if (i%2)
            cout<<i+1<<" |█";
        else
            cout<<i+1<<" | ";

        for (int j=0;j<8;++j)
            if (board[j][i]){
                if ((i+j)%2)
                    cout<<board[j][i]->Colour()<<board[j][i]->Type()<<"█| ";
                else if(j==7)
                    cout<<board[j][i]->Colour()<<board[j][i]->Type()<<" | ";
                else
                    cout<<board[j][i]->Colour()<<board[j][i]->Type()<<" |█";
            }
            else {
                if ((i+j)%2)
                    cout<<"███| ";
                else if(j==7)
                    cout<<"   | ";
                else
                    cout<<"   |█";
            }
        cout<<i+1<<endl;
        cout<<"   ---------------------------------------"<<endl;
    }

    cout<<"     A    B    C    D    E    F    G    H \n"<<endl;
    cout<<"Options: A1-A2, 0-0, 0-0-0, save, load, exit"<<endl;
}

int CBoard::Move(const string & move, char turn){

    // check castling
    if (move=="0-0")
        return castling(4, 7, turn);
    if (move=="0-0-0")
        return castling(4, 0,turn);
    
    if (move.size()<5) 
        return 2;
    
    int toRow=move[4]-49, toCol=toupper(move[3])-65, fromRow=move[1]-49, fromCol=toupper(move[0])-65;
    
    // check if squares are valid
    if (fromCol > 7 || fromCol<0 ||
        toCol > 7 || toCol<0 ||
        fromRow > 7 || fromRow < 0 ||
        toRow > 7 || toRow < 0 ||
        !board[fromCol][fromRow])
        return 2;
    
    // check the colour of moving piece and player's colour
    if (board[fromCol][fromRow]->Colour() != turn)
        return 3;
    
    // check if destination square is not occupied by own piece
    if (board[toCol][toRow] && board[toCol][toRow]->Colour() == turn)
        return 4;
    
    // check en passant square
    if (board[fromCol][fromRow]->Type()=='P' && enp[0]==toCol && enp[1]==toRow)
        if ((turn=='W' && toRow==5) || (turn=='B' && toRow==2)){
            int offset=turn=='W'?-1:1;
            board[toCol][toRow] = board[enp[0]][enp[1]+offset];
            board[enp[0]][enp[1]+offset]=NULL;
        }
    
    // check if move is valid for piece
    if (!board[fromCol][fromRow]->ValidMove(fromCol, fromRow, toCol, toRow,board))
        return 5;
    
    // make move
    CPiece* tmp = board[toCol][toRow];
    board[toCol][toRow] = board[fromCol][fromRow];
    board[fromCol][fromRow]=NULL;
    
    // check if is not in check
    if (inCheck(turn)){
        // undo move
        board[fromCol][fromRow]=board[toCol][toRow];
        board[toCol][toRow]=tmp;
        return 6;
    }
    else delete tmp;
    
    // unset en passant position
    enp[0]=8;
    enp[1]=8;
    
    // disable castling if king or rook moves
    if (board[toCol][toRow]->Type()=='K'){
        if (board[toCol][toRow]->Colour()=='W')
            cast[0]=cast[1]=0;
        else if (board[toCol][toRow]->Colour()=='B')
            cast[2]=cast[3]=0;
    }
    else if (board[toCol][toRow]->Type()=='R'){
        if (fromCol==0){
            if (board[toCol][toRow]->Colour()=='W')
                cast[0]=0;
            else if(board[toCol][toRow]->Colour()=='B')
                cast[2]=0;
        }
        else if (fromCol==7){
            if (board[toCol][toRow]->Colour()=='W')
                cast[1]=0;
            else if(board[toCol][toRow]->Colour()=='B')
                cast[3]=0;
        }
    }
    
    // check promotion and set en passant position
    else if (board[toCol][toRow]->Type()=='P'){
        if (toRow==7 || toRow==0)
            return promotion(toCol, toRow, turn);
        else if (toRow==3 || toRow==4){
            enp[0]=toCol;
            enp[1]= turn=='W'?toRow-1:toRow+1;
        }
    }
    return 1;
}

bool CBoard::inCheck(char player) const{
    int kingCol, kingRow;

    // find the king position
    for (int i=0;i<8;++i)
        for (int j=0;j<8;++j)
            if (board[i][j] && board[i][j]->Colour()==player && board[i][j]->Type()=='K'){
                kingCol=i;
                kingRow=j;
            }
    
    // check if some piece can remove king
    for (int i=0;i<8;++i)
        for (int j=0;j<8;++j)
            if (board[i][j] && board[i][j]->Colour() != player && board[i][j]->ValidMove(i, j, kingCol, kingRow, board))
                return true;

    return false;
}

bool CBoard::canMove(char player){
    bool canMove;

    // find all player's pieces
    for (int i = 0; i<8; ++i)
        for (int j = 0; j<8; ++j)
            if (board[i][j] && board[i][j]->Colour()==player)

                // check if a piece can move
                for (int dCol=0; dCol<8; ++dCol)
                    for (int dRow=0; dRow<8; ++dRow)
                        if (((board[dCol][dRow] && board[dCol][dRow]->Colour() != player) ||
                            !board[dCol][dRow]) &&
                            board[i][j]->ValidMove(i, j, dCol, dRow, board)){

                            // make move
                            CPiece* tmp = board[dCol][dRow];
                            board[dCol][dRow] = board[i][j];
                            board[i][j]=NULL;
                            canMove=!inCheck(player);

                            // undo move
                            board[i][j]=board[dCol][dRow];
                            board[dCol][dRow]=tmp;
                            if (canMove)
                                return true;
                        }
    
    return false;
}

int CBoard::castling(int kingCol, int rookCol, char player){
    int  rookRow, kingRow, offset;
    rookRow = kingRow = player=='W' ? 0:7;
    
    // check if rook or king was moved
    if (rookCol==0){
        if (rookRow==0 && !cast[0])
            return 7;
        else if (rookRow==7 && !cast[2])
            return 7;
    }
    else if (rookCol==7){
        if (rookRow==0 && !cast[1])
            return 7;
        else if (rookRow==7 && !cast[3])
            return 7;
    }
    
    // check all squares between rook and king and if king is not in check while moving
    offset = rookCol > kingCol ? 1 : -1;
    if (inCheck(player))
        return 9;
    for (int col=kingCol+offset; col!=kingCol+3*offset; col+=offset){
        if (board[col][kingRow])
            return 8;
        board[col][kingRow] = board[col-offset][kingRow];
        board[col-offset][kingRow]=NULL;
        if (inCheck(player)){
            board[kingCol][kingRow]=board[col][kingRow];
            return 9;
        }
    }
    if (rookCol==0 && board[rookCol-offset][rookRow])
        return 8;
    
    // move rook
    board[kingCol+offset][rookRow] = board[rookCol][rookRow];
    board[rookCol][rookRow]=NULL;
    
    // disable next castling
    if (kingRow==0)
        cast[0]=cast[1]=0;
    else
        cast[2]=cast[3]=0;
    
    return 1;
}

bool CBoard::promotion(int col, int row, char turn){
    char type;
    bool invalid;

    cout<<"Choose type of piece you promote to (R, N, B or Q): ";
    do{
        cin>>type;
        invalid=false;
        if (type !='R' && type !='N' && type !='B' && type !='Q'){
            cout<<"invalid type, choose again: ";
            invalid=true;
        }
    }while (invalid);
    
    delete board[col][row];

    switch (type) {
        case 'R':
            board[col][row] = new CRook(turn);
            break;
        case 'N':
            board[col][row] = new CKnight(turn);
            break;
        case 'B':
            board[col][row] = new CBishop(turn);
            break;
        case 'Q':
            board[col][row] = new CQueen(turn);
            break;
    }
    return true;
}

void CBoard::Save(ofstream & f) const{
    for (int i = 0; i<8; ++i)
        for (int j = 0; j<8; ++j)
            if (board[i][j] )f<<board[i][j]->Colour()<<" "<<board[i][j]->Type()<<" ";
            else f<<"0 0 ";

    f<<enp[0]<<" "<<enp[1]<<" ";
    f<<cast[0]<<" "<<cast[1]<<" "<<cast[2]<<" "<<cast[3]<<" ";
}

void CBoard::Load(ifstream & f){
    char type, colour;

    for (int i = 0; i<8; ++i)
        for (int j = 0; j<8; ++j){
            delete board[i][j];
            f>>colour>>type;
            switch (type) {
                case '0':
                    board[i][j]=NULL;
                    break;
                case 'P':
                    board[i][j]=new CPawn(colour);
                    break;
                case 'R':
                    board[i][j]=new CRook(colour);
                    break;
                case 'N':
                    board[i][j]=new CKnight(colour);
                    break;
                case 'B':
                    board[i][j]=new CBishop(colour);
                    break;
                case 'Q':
                    board[i][j]=new CQueen(colour);
                    break;
                case 'K':
                    board[i][j]=new CKing(colour);
                    break;
            }
        }

    f>>enp[0]>>enp[1];
    f>>cast[0]>>cast[1]>>cast[2]>>cast[3];
}

