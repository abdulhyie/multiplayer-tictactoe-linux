#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "aux.h"

using namespace std;

string p = "Player 1";

int main()
{
    initBoard();

    mkfifo("board", 0666);
    ifstream f("time.txt", ios::in);

    int pipe;

    while (1)
    {
        displayBoard();
        cout << "Your move... " << endl;
        placeToken('X', p);
        pipe = open("board", O_WRONLY);
        if (checkWinningCond()) {
            system("clear");
            displayBoard();
            write(pipe, "LLLLLLLLL", 9);
            cout << "CONGRATULATIONS! You won!" << endl;
            close(pipe);
            return 0;
        }
        if (occupiedPlaces <= 0){
            system("clear");
            displayBoard();
            write(pipe, "DDDDDDDD", 9);
            cout << "DRAW! No one won!" << endl;
            close(pipe);
            return 0;
        }
        write(pipe, boardArr, 9);
        close(pipe);

        system("clear");
        displayBoard();
        cout << "Waiting for your opponent move...." << endl;
        pipe = open("board", O_RDONLY);
        read(pipe, boardArr, 9);
        if (boardArr[0][0] == 'L'){
            system("clear");
            displayBoard();
            cout << "HARD LUCK! You lost!" << endl;
            close(pipe);
            return 0;
        }
        if (boardArr[0][0] == 'D'){
            system("clear");
            displayBoard();
            cout << "DRAW! No one won!" << endl;
            close(pipe);
            return 0;
        }
        close(pipe);
        system("clear");
    }
}