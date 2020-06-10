#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include <chrono>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

int p1Score = 0, p2Score = 0, p1HScore, p2HScore;

//threads data
pthread_mutex_t time_lock;
pthread_cond_t xy_read;
bool done;
pthread_t t_time, t_high_score;

//threads functions
void* getTime(void *args) {
	auto start = high_resolution_clock::now();
	while (!done) {
		//wait for the signal
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	cout << endl << "Time taken to select: " << duration.count() << " seconds." << endl << endl << endl;
}
void* writeHighScore(void *args) {
	fstream in;
	in.open("high-score.txt", ios::in);
	int score1, score2;
	in >> score1 >> score2;
	if (p1Score > score1){
		score1 = p1Score;
	}
	if (p2Score > score2){
		score2 = p2Score;
	}
	in.close();
	fstream out;
	out.open("high-score.txt", ios::out);
	out << score1 << ' ' << score2;
	out.close();
}

class TicTacToe {
private:
	int mode, occupiedPlaces;
	string p1Name, p2Name;
	bool gameOver;
	bool turns;
	char board[3][3];
public:
	TicTacToe() {
		gameOver = turns = false;
		occupiedPlaces = 9;
		mode = 3;		//assign any value other than 1 or 2
		//initialize the board with '-'
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = '-';
			}
		}
		time_lock = PTHREAD_MUTEX_INITIALIZER;
		xy_read = PTHREAD_COND_INITIALIZER;
	}
	bool checkWinningCond() {
		//This checks for all the columns
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				if (board[j][i] == '-' || board[j][i] != board[j + 1][i]) {
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
				if (board[i][j] == '-' || board[i][j] != board[i][j + 1]) {
					break;
				}
				if (j == 1) {
					return true;
				}
			}
		}
		// this checks for right diagonal
		for (int i = 0; i < 2; i++) {
			if (board[i][i] == '-' || board[i][i] != board[i + 1][i + 1])
				break;
			if (i == 1) {
				return true;
			}
		}
		//this checks for left diagonal
		for (int i = 0; i < 2; i++) {
			if (board[2 - i][i] == '-' || board[2 - i][i] != board[2 - i - 1][i + 1])
				break;
			if (i == 1) {
				return true;
			}
		}
		return false;
	}
	void menu()
	{
		while (mode != 1 && mode != 2) {
			cout << "WELCOME! Please select the mode you want to play." << endl << endl << "1- 1v1\t\t\t2- 1vComputer" << endl << endl;
			cout << "Enter: ";
			cin >> mode;
			if (mode != 1 && mode != 2) {
				cout << "Invalid input. Please Enter again." << endl;
			}
			//If user selects 1v1, ask both player names
			if (mode == 1) {
				cout << "Player 1 Name: ";
				cin >> p1Name;
				cout << "Player 2 Name: ";
				cin >> p2Name;
			}
			//if user selects 1vComp, ask only player's name
			else {
				cout << "Player Name: ";
				cin >> p1Name;
				p2Name = "CPU";
			}
		}
	//	clear();
	}
	void displayBoard()
	{
		cout << endl << endl << "----------------------------------" << endl << endl;
		cout << "Mode: " << p1Name << " vs. " << p2Name << endl << endl;
		cout << "" << p1Name << ": X\t\t" << p2Name << ": 0" << endl << endl;
		cout << p1Name << " Score: " << p1Score << "\t\t" << p2Name << " Score: " << p2Score << endl << endl; 
		if (!turns)	cout << p1Name << "'s turn: O" << endl << endl;
		else cout << p2Name << "'s turn: X" << endl << endl;
		cout << " 	 Column 0   Column 1   Column 2 " << endl
			<< " 	________________________________" << endl
			<< " 	|         |          |         |" << endl
			<< " Row 0	|    " << board[0][0] << "    |     " << board[0][1] << "    |    " << board[0][2] << "    |" << endl
			<< " 	|_________|__________|_________|" << endl
			<< " 	|         |          |         |" << endl
			<< " Row 1	|    " << board[1][0] << "    |     " << board[1][1] << "    |    " << board[1][2] << "    |" << endl
			<< " 	|_________|__________|_________|" << endl
			<< " 	|         |          |         |" << endl
			<< " Row 2	|    " << board[2][0] << "    |     " << board[2][1] << "    |    " << board[2][2] << "    |" << endl
			<< " 	|_________|__________|_________|" << endl << endl << endl;
	}
	void changeTurn() {
		if (turns == true) {
			turns = false;
		}
		else
			turns = true;
	}
	void getXY() {
		int x, y;
		if (mode == 2 && !turns) {
			x = y = 3;
			do {
				srand(time(0));
				x = rand() % 3;
				y = rand() % 3;
			} while (board[x][y] == 'X' || board[x][y] == 'O');
		}
		else {
			done  = false;
			pthread_create(&t_time, NULL, getTime, NULL);
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
				if (board[x][y] == 'X' || board[x][y] == 'O') {
					cout << "Place alreday occupied!" << endl;
				}
			} while (board[x][y] == 'X' || board[x][y] == 'O');
			done = true;	//signal the thread;
			pthread_join(t_time, NULL);
		}
		placeToken(x, y);
		x = y = 3;
		occupiedPlaces--;
	}
	void placeToken(int x, int y) {
		if (turns) {
			board[x][y] = 'O';
		}
		else board[x][y] = 'X';
	}
	void run() {
		menu();
		while (!gameOver) {
			system("clear");
			displayBoard();
			getXY();
			changeTurn();
			if (checkWinningCond()) {
				system("clear");
				displayBoard();
				if (!turns) {
					cout << endl << endl << p2Name << " has WON the game." << endl;
					p2Score++;
				}
				else {
					cout << endl << endl << p1Name << " has WON the game." << endl;
					p1Score++;
				}
				//update the high scores in high-score.txt file
				pthread_create(&t_high_score, NULL, writeHighScore, NULL);
				pthread_join(t_high_score, NULL);
				return;
			}
			if (occupiedPlaces == 0){
				cout << endl << endl << "It's a draw, no one won!" << endl;
			}
		}
	}
	bool reset(){
		char opt = 'x';
		while (opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N'){
			cout << "Do you want tp play gain? [y/n]: ";
			cin >> opt;
			if (opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N'){
				cout << "Invalid selection!" << endl;
			}
		}
		cout << endl << "-------------------------" << endl << endl;
		if (opt == 'n' || opt == 'N')	return false;
		else{
			gameOver = turns = false;
		occupiedPlaces = 9;
		mode = 3;		//assign any value other than 1 or 2
		//initialize the board with '-'
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = '-';
			}
		}
		time_lock = PTHREAD_MUTEX_INITIALIZER;
		xy_read = PTHREAD_COND_INITIALIZER;
		return true;
		}
	}
};

int main()
{
	TicTacToe game;
	do{
		game.run();
	}while (game.reset());
}
