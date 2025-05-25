#include "Piece.h"  // Include the header file for the Piece class

// Constructor
Piece::Piece(char color) {
    this->color = color;   // Initialize the color ('r' for red, 'b' for black)
    this->isKing = false;  // All pieces start as non-kings by default
}

// Accessors

// Returns the color of the piece ('r' or 'b')
char Piece::getColor() const {
    return color;
}

// Returns whether the piece is a king
bool Piece::getIsKing() const {
    return isKing;
}

// Mutators

// Promote the piece to a king
void Piece::promote() {
    isKing = true;
}

// Utility: Get a symbol representing the piece for board display
char Piece::getSymbol() const {
    // If the piece is red, return 'R' if it's a king, otherwise 'r'
    if (color == 'r') {
        return isKing ? 'R' : 'r';  // Capital R for red king
    }
    // If the piece is black, return 'B' if it's a king, otherwise 'b'
    else {
        return isKing ? 'B' : 'b';  // Capital B for black king
    }
}