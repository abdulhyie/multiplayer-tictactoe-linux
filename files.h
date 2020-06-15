#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
using namespace std::chrono;

//game data
char boardArr[3][3];
string p1Name, p2Name;
int occupiedPlaces = 9;
int p1Score = 0, p2Score = 0;
int timeTaken = 0;

//threads data
bool done;
pthread_t t_time, t_high_score;

//thread functions
void* getTime(void *args) {
	auto start = high_resolution_clock::now();
	while (!done) {
		//wait for the signal
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
    ofstream out("time.txt", ios::app);
    out << *static_cast<string*>(args) << ": " << duration.count() << endl;
    out.close();
}
void* writeHighScore(void *args) {
	fstream in;
	in.open("high-score.txt", ios::in);
	int score1, score2;
    string p, pArg = *static_cast<string*>(args);
    in >> p;
    if (p == "Player1:"){
        in >> score1;
        in >> p;
        in >> score2;
    }
    else{
        in >> score2;
        in >> p;
        in >> score1;
    }
    in.seekg(0, ios::beg);
	in >> p;
	if (p == pArg && p == "Player1:"){
        score1++;
	}
	else {
		score2++;
	}
	in.close();
    fstream out("high-score.txt", ios::out);
    out << "Player1: " << score1 << endl << "Player2: " << score2 << endl;
	out.close();
}

//game functions
void initBoard()
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
        boardArr[i][j] = '-';
        }
    }
    //intialize the time.txt file with 0
    ofstream out("time.txt", ios::out);
    out << "Time taken by players. (in seconds)" << endl;
    out.close();
}
void displayBoard()
{
    cout << " 	 Column 0   Column 1   Column 2 " << endl
        << " 	________________________________" << endl
        << " 	|         |          |         |" << endl
        << " Row 0	|    " << boardArr[0][0] << "    |     " << boardArr[0][1] << "    |    " << boardArr[0][2] << "    |" << endl
        << " 	|_________|__________|_________|" << endl
        << " 	|         |          |         |" << endl
        << " Row 1	|    " << boardArr[1][0] << "    |     " << boardArr[1][1] << "    |    " << boardArr[1][2] << "    |" << endl
        << " 	|_________|__________|_________|" << endl
        << " 	|         |          |         |" << endl
        << " Row 2	|    " << boardArr[2][0] << "    |     " << boardArr[2][1] << "    |    " << boardArr[2][2] << "    |" << endl
        << " 	|_________|__________|_________|" << endl << endl << endl;
}
void placeToken(char token, string pName) {
    int x, y;
    done  = false;
    pthread_create(&t_time, NULL, getTime, &pName);
    do {
        x = y = 3;		//give any value exept 0, 1, 2
        while (x < 0 || x > 2) {
            cout << "Enter row: ";
            cin >> x;
            if (x < 0 || x > 2)	cout << "Invalid!" << endl;
        }
        while (y < 0 || y > 2) {
            cout << "Enter column: ";
            cin >> y;
            if (y < 0 || y > 2)	cout << "Invalid!" << endl;
        }
        if (boardArr[x][y] == 'X' || boardArr[x][y] == 'O') {
            cout << "Place alreday occupied!" << endl;
        }
    } while (boardArr[x][y] == 'X' || boardArr[x][y] == 'O');
    done = true;	//signal the thread;
    pthread_join(t_time, NULL);
    //now place the token
    boardArr[x][y] = token;
    occupiedPlaces -= 2;
}
bool checkWinningCond() {
    //This checks for all the columns
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            if (boardArr[j][i] == '-' || boardArr[j][i] != boardArr[j + 1][i]) {
                break;
            }
            if (j == 1) {
                return true;
            }
        }
    }
    //This checks for all the rows
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            if (boardArr[i][j] == '-' || boardArr[i][j] != boardArr[i][j + 1]) {
                break;
            }
            if (j == 1) {
                return true;
            }
        }
    }
    // this checks for right diagonal
    for (int i = 0; i < 2; i++) {
        if (boardArr[i][i] == '-' || boardArr[i][i] != boardArr[i + 1][i + 1])
            break;
        if (i == 1) {
            return true;
        }
    }
    //this checks for left diagonal
    for (int i = 0; i < 2; i++) {
        if (boardArr[2 - i][i] == '-' || boardArr[2 - i][i] != boardArr[2 - i - 1][i + 1])
            break;
        if (i == 1) {
            return true;
        }
    }
    return false;
}