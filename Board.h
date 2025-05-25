#ifndef BOARD_H
#define BOARD_H

#include <vector>     // For using std::vector
#include "Piece.h"    // Include Piece class for board pieces

// Board class manages the game grid and handles game logic
class Board {
private:
    // 2D grid of pointers to Piece objects representing the game board
    std::vector<std::vector<Piece*>> grid;

public:
    Board();              // Constructor to initialize the board
    ~Board();             // Destructor to clean up dynamically allocated Piece objects

    void initialize();    // Initializes the board with pieces in their starting positions
    void display() const; // Prints the board to the console

    // Checks if a move is valid based on piece movement and rules
    bool isValidMove(int x1, int y1, int x2, int y2, char playerColor) const;

    // Attempts to move a piece; updates wasCapture if a capture occurred
    bool makeMove(int x1, int y1, int x2, int y2, bool& wasCapture);

    // Checks if a player has any legal moves left
    bool hasAnyValidMoves(char playerColor) const;

    // Returns a pointer to the Piece at a specific location on the board
    Piece* getPieceAt(int x, int y) const;

    // Determines if a piece at (x, y) has a valid jump (capture) move
    bool hasJumpAvailable(int x, int y) const;
};

#endif
#pragma once