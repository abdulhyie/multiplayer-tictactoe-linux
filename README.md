# Multiplayer Tic Tac Toe for Linux in cpp
Multiplayer Tic Tac Toe implemented using named pipes and threads in linux.

## Requirements
* Linux
* C++

## How to run
1. Open two terminals in the directory containg source code
2. On first terminal, run this command:
  ```Bash
  c++ player1.cpp -lpthread -o p1
  ```
3. On second terminal, run this command:
  ```Bash
  c++ player2.cpp -lpthread -o p2
  ```
4. Again on the first terminal, run this command:
  ```Bash
  ./p1.out
  ```
5. On second terminal, run this command:
  ```Bash
  ./p2.out
  ```
6. Game will start, enter the co-ordinates and play.
  
**Demo**

![Demo](https://github.com/abdulhyie/multiplayer-tictactoe-linux/blob/master/imgs/01.JPG?raw=true)

![Demo](https://github.com/abdulhyie/multiplayer-tictactoe-linux/blob/master/imgs/02.JPG?raw=true)
