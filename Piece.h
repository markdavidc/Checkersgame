#ifndef PIECE_H
#define PIECE_H

// The Piece class represents a single checker piece
class Piece {
private:
    char color;   // 'r' for red or 'b' for black to indicate the piece's color
    bool isKing;  // True if the piece is a king, false otherwise

public:
    // Constructor
    Piece(char color); // Initializes a piece with a given color; not a king by default

    // Accessors (getters)
    char getColor() const;     // Returns the color of the piece
    bool getIsKing() const;    // Returns whether the piece is a king

    // Mutators (setters)
    void promote();            // Promotes the piece to a king

    // Utility
    char getSymbol() const;    // Returns the symbol used to display the piece on the board
    // Lowercase for regular, uppercase for king
};

#endif 


