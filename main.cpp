#include <iostream>
#include "Board.h"

int main() {
    Board board;
    char currentPlayer = 'r';

    while (true) {
        board.display();
        std::cout << "\nCurrent turn: " << (currentPlayer == 'r' ? "Red" : "Black") << "\n";

        int x1, y1, x2, y2;
        std::cout << "Enter source coordinates (row col): ";
        std::cin >> x1 >> y1;
        std::cout << "Enter destination coordinates (row col): ";
        std::cin >> x2 >> y2;

        bool wasCapture = false;
        if (board.makeMove(x1, y1, x2, y2, wasCapture)) {
            int newX = x2;
            int newY = y2;

            // Multi-jump loop
            while (wasCapture && board.hasJumpAvailable(newX, newY)) {
                board.display();
                std::cout << "\nYou made a capture! Another jump is available.\n";
                std::cout << "Enter next jump move from (" << newX << ", " << newY << "): ";
                std::cin >> x2 >> y2;

                x1 = newX;
                y1 = newY;
                if (!board.makeMove(x1, y1, x2, y2, wasCapture)) {
                    std::cout << "Invalid multi-jump move. Turn ends.\n";
                    break;
                }
                newX = x2;
                newY = y2;
            }

            // Check win condition
            char nextPlayer = (currentPlayer == 'r') ? 'b' : 'r';
            if (!board.hasAnyValidMoves(nextPlayer)) {
                board.display();
                std::cout << (nextPlayer == 'r' ? "Red" : "Black") << " has no valid moves left. "
                    << (currentPlayer == 'r' ? "Red" : "Black") << " wins!\n";
                break;
            }

            currentPlayer = nextPlayer;
        }
        else {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    return 0;
}
