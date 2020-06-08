#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<windows.h>
#include<ctime>

using namespace std;

void menu();
void display();
void input();
void gameplay();

int mode;
bool gameOver = false;
bool turns = false;
int rows, cols;
char mark[3][3];

int main()
{
	menu();
	while (!gameOver){
		display();
		input();
		gameplay();
		system("cls");
		if (turns == true){
			turns = false;
		}
		else
			turns = true;
	}
	if (turns == false){
		display();
		cout << endl << endl << "Player (2) won the game.";
	}
	else{
		display();
		cout << endl << endl << "Player (1) won the game.";
	}
	system("pause>0");
}

void menu()
{
	cout << setw(35) << ".:: TicTacToe ::." << endl << setw(40) << ".:: Made by Abdul Hai ::." << endl << endl << endl
		<< "WELCOME! Please select the mode you want to play." << endl << endl << "1- 1v1\t\t\t2- 1vComputer" << endl << endl ;
mode_check:
	cout << "Enter: ";
	cin >> mode;
	if (mode != 1 && mode != 2){
		cout << "Invalid input. Please Enter again." << endl;
		goto mode_check;
	}
	system("cls");
}
void display()
{
	cout << setw(35) << ".:: TicTacToe ::." << endl << setw(40) << ".:: Made by Abdul Hai ::." << endl;
	if (mode == 1){
		cout << setw(31) << "Mode: 1v1" << endl << endl << endl;
	}
	else
		cout << setw(35) << "Mode: 1vComputer" << endl << endl << endl;
	cout << " 	 Column 0   Column 1   Column 2 " << endl
		<<	" 	________________________________" << endl
		<< " 	|         |          |         |" << endl
		<< " Row 0	|    " << mark[0][0] << "    |     " << mark[0][1] << "    |    " << mark[0][2] << "    |" << endl
		<< " 	|_________|__________|_________|" << endl
		<< " 	|         |          |         |" << endl
		<< " Row 1	|    " << mark[1][0] << "    |     " << mark[1][1] << "    |    " << mark[1][2] << "    |" << endl
		<< " 	|_________|__________|_________|" << endl
		<< " 	|         |          |         |" << endl
		<< " Row 2	|    " << mark[2][0] << "    |     " << mark[2][1] << "    |    " << mark[2][2] << "    |" << endl
		<< " 	|_________|__________|_________|" << endl;
}
void input()
{
	if (mode == 1){
		if (turns == false){
		row_check:
			cout << endl << "-------------------------------------------" << endl << endl;
			cout << "Player (1) turn: ";
			cout << endl << "Enter Row: ";
			cin >> rows;
			if (rows > 2 || rows < 0){
				cout << "Invalid input. Enter Again.";
				goto row_check;
			}
		col_check:
			cout << "Enter colums: ";
			cin >> cols;
			if (cols > 2 || cols < 0){
				cout << "Invalid input. Enter Again.";
				goto col_check;
			}
			if (mark[rows][cols] == 'X' || mark[rows][cols] == 'O'){
				cout << endl << "Spot is already occupied. Enter again." << endl;
				goto row_check;
			}
			else
				mark[rows][cols] = 'X';
		}
		else{
		row_check1:
			cout << endl << "-------------------------------------------" << endl << endl;
			cout << "Player (2) turn: ";
			cout << endl << "Enter Row: ";
			cin >> rows;
			if (rows > 2 || rows < 0){
				cout << "Invalid input. Enter Again.";
				goto row_check1;
			}
		col_check1:
			cout << "Enter colums: ";
			cin >> cols;
			if (cols > 2 || cols < 0){
				cout << "Invalid input. Enter Again.";
				goto col_check1;
			}
			if (mark[rows][cols] == 'X' || mark[rows][cols] == 'O'){
				cout << endl << "Spot is already occupied. Enter again." << endl;
				goto row_check1;
			}
			else
				mark[rows][cols] = 'O';
		}
	}
	else{
		if (turns == false){
		row_check3:
			cout << endl << "-------------------------------------------" << endl << endl;
			cout << "Your turn: ";
			cout << endl << "Enter Row: ";
			cin >> rows;
			if (rows > 2 || rows < 0){
				cout << "Invalid input. Enter Again.";
				goto row_check3;
			}
		col_check3:
			cout << "Enter colums: ";
			cin >> cols;
			if (cols > 2 || cols < 0){
				cout << "Invalid input. Enter Again.";
				goto col_check3;
			}
			if (mark[rows][cols] == 'X' || mark[rows][cols] == 'O'){
				cout << endl << "Spot is already occupied. Enter again." << endl;
				goto row_check3;
			}
			else
				mark[rows][cols] = 'X';
		}
		else{
			cout << endl << "-------------------------------------------" << endl << endl;
			cout << "Computer turn. ";
		row_check2:
			rows = rand() % 3;
			cols = rand() % 3;
			cout << cols;
			if (mark[rows][cols] == 'X' || mark[rows][cols] == 'O'){
				goto row_check2;
			}
			else{
				cout << endl << "Row: ";
				Sleep(1000);
				cout << rows << endl;;
				cout << "Colums: ";
				Sleep(1000);
				cout << cols;
				mark[rows][cols] = 'O';
			}
		}
	}
}
void gameplay()
{
	if (turns == false){
		for (int i = 0; i<3; i++){
			if (mark[0][i] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[1][i] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[2][i] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][0] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][1] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][2] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][i] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0, j = 2; i<3; i++, j--){
			if (mark[i][j] != 'X'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
	}
	else{
		for (int i = 0; i<3; i++){
			if (mark[0][i] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[1][i] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[2][i] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][0] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][1] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][2] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0; i<3; i++){
			if (mark[i][i] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
		for (int i = 0, j = 2; i<3; i++, j--){
			if (mark[i][j] != 'O'){
				break;
			}
			if (i == 2){
				gameOver = true;
			}
		}
	}
}
