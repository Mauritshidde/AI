#include <iostream>
#include <vector>

#include "Qlearningt.h"

// void bestMoveAI() {
// }

bool movePossible(std::vector<int>* board, int value, int move) {
    if (board->at(move) != 0) {
        return false;
    }
    return true;
}

void makeMove(int turn, std::vector<int>* board) {
    int choice;
    if (turn == 0) {
        std::cout << "Where do you want to place a X " << std::endl;
        std::cin >> choice;
        if (movePossible(board, 1, choice)) {
            board->at(choice) = 1;
        } else {
            std::cout << " ja ";
            makeMove(turn, board);

        }

    } else if (turn == 1) {
        // choice = QAI
    } else {
        board->at(choice) = 1;
        // choice = AI
    }
} 

void printBoard(std::vector<int>* board) {
    for (int i=0; i < 9; i++) {
        if (i == 0 || i == 3 || i == 6) {
            std::cout << std::endl;
        }
        
        if (board->at(i) == 1) {
            std::cout << "x";
        } else if (board->at(i) == 2) {
            std::cout << "O";
        } else {
            std::cout << "-";
        }
    }
}

bool checkWin(std::vector<int>* board, int value) {
    if (board->at(0) == value && board->at(1) == value && board->at(2) == value) {
        return true;
    } else if (board->at(3) == value && board->at(4) == value && board->at(5) == value) {
        return true;
    } else if (board->at(6) == value && board->at(7) == value && board->at(8) == value) {
        return true;
    } else if (board->at(0) == value && board->at(3) == value && board->at(6) == value) {
        return true;
    } else if (board->at(1) == value && board->at(4) == value && board->at(7) == value) {
        return true;
    } else if (board->at(2) == value && board->at(5) == value && board->at(8) == value) {
        return true;
    } else if (board->at(0) == value && board->at(4) == value && board->at(8) == value) {
        return true;
    } else if (board->at(2) == value && board->at(4) == value && board->at(6) == value) {
        return true;
    } else {
        return false;
    }
}


void game() {
    Qlearning Qtable;
    std::vector<int> board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool door = true;
    int turn = 1;
    while (door) {
        if (turn == 1) {
            // makeMove(0, &board);
            // turn++;
            // printBoard(&board);
            // if (checkWin(&board, 1)) {
            //     door = false;
            //     std::cout << std::endl << "end" << std::endl;
            // }


            std::vector<bool> checkBoard;
            for (int i=0; i < board.size(); i++) {
                if (board.at(i) == 0) {
                    checkBoard.push_back(false);
                } else {
                    checkBoard.push_back(true);
                }
            }
            int choice = Qtable.makeDecision(&board, &checkBoard);
            // std::cout << choice << " n33" << std::endl;
            board.at(choice) = 1;
            turn -= 1;
            printBoard(&board);
            std::cout << std::endl;
            if (checkWin(&board, 1)) {
                door = false;
                // std::cout << std::endl << "end" << std::endl;
                Qtable.Reward(false, &board);
                Qtable.saveQtable();
            }
        } else {
            // makeMove(1, &board);
            std::vector<bool> checkBoard;
            for (int i=0; i < board.size(); i++) {
                if (board.at(i) == 0) {
                    checkBoard.push_back(false);
                } else {
                    checkBoard.push_back(true);
                }
            }
            int choice = Qtable.makeDecision(&board, &checkBoard);
            // std::cout << choice << " ja" << std::endl;
            board.at(choice) = 2;
            turn += 1;
            printBoard(&board);
            std::cout << std::endl;
            if (checkWin(&board, 2)) {
                door = false;
                // std::cout << std::endl << "end" << std::endl;
            }
        }
        
    }
}

int main() {
    // while (true) {
    //     game();
    // }

    for (int i=0; i < 100; i++) {
        game();
    }



    return 0;
}