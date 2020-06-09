#include <iostream>
#include <string>
//#include <ncurses.h>
#include <ctime>
#include <unistd.h>

using namespace std;

class TicTacToe {
private:
	int mode;
	string p1Name, p2Name;
	bool gameOver = false;
	bool turns = false;
	char board[3][3];
public:
	TicTacToe() {
		mode = 3;		//assign any value other than 1 or 2
		//initialize the board
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = '-';
			}
		}
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
		cout << "\tMode: " << p1Name << " vs. " << p2Name << endl;
		cout << "\t" << p1Name << ": X\t\t" << p2Name << ": 0" << endl << endl << endl;
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
		}
		placeToken(x, y);
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
			displayBoard();
			getXY();
			changeTurn();
			if (checkWinningCond()) {
			//	clear();
				displayBoard();
				if (!turns) {
					cout << endl << endl << p2Name << " has WON the game." << endl;
				}
				else {
					cout << endl << endl << p1Name << " has WON the game." << endl;
				}
				cout << "Press any key to continue." << endl;
			//	getch();
				return;
			}
		//	clear();
		}
		cout << "Press any key to continue." << endl;
	//	getch();
	}
};

int main()
{
	TicTacToe game;
	game.run();
}
