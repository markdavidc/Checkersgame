#include "Board.h"
#include <iostream>
#include <iomanip>

// Constructor: sets up an 8x8 grid of Piece pointers, initially all nullptr, then calls initialize()
Board::Board() {
    grid.resize(8, std::vector<Piece*>(8, nullptr));
    initialize();
}

// Destructor: deallocates all dynamically allocated Piece objects
Board::~Board() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete grid[row][col];
        }
    }
}

// Initializes the board with red and black pieces in the standard starting positions
void Board::initialize() {
    // Place red pieces (top 3 rows)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {  // Only place pieces on black squares
                grid[row][col] = new Piece('r');
            }
        }
    }

    // Place black pieces (bottom 3 rows)
    for (int row = 5; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                grid[row][col] = new Piece('b');
            }
        }
    }
}

// Displays the current state of the board in the console
void Board::display() const {
    std::cout << "  ";
    for (int col = 0; col < 8; ++col)
        std::cout << col << " ";
    std::cout << "\n";

    for (int row = 0; row < 8; ++row) {
        std::cout << row << " ";
        for (int col = 0; col < 8; ++col) {
            if (grid[row][col] == nullptr)
                std::cout << ". ";  // Empty square
            else
                std::cout << grid[row][col]->getSymbol() << " ";  // Show piece symbol
        }
        std::cout << "\n";
    }
}

// Safely retrieves the Piece at (x, y), or nullptr if out of bounds
Piece* Board::getPieceAt(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
        return nullptr;
    return grid[x][y];
}

// Checks whether a move is valid for the given playerColor
bool Board::isValidMove(int x1, int y1, int x2, int y2, char playerColor) const {
    // 1. Check bounds
    if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 ||
        x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8)
        return false;

    Piece* source = grid[x1][y1];
    Piece* dest = grid[x2][y2];

    // 2. Check that the source has the player's piece
    if (!source || source->getColor() != playerColor)
        return false;

    // 3. Destination must be empty
    if (dest != nullptr)
        return false;

    int dx = x2 - x1;
    int dy = y2 - y1;

    // 4. Determine forward direction based on color
    int direction = (playerColor == 'r') ? 1 : -1;

    // 5. Check for regular move
    if (abs(dx) == 1 && abs(dy) == 1) {
        if (source->getIsKing() || dx == direction)
            return true;
        else
            return false;
    }

    // 6. Check for capture (jump)
    if (abs(dx) == 2 && abs(dy) == 2) {
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        Piece* middle = grid[midX][midY];

        if (middle && middle->getColor() != playerColor) {
            if (source->getIsKing() || dx == 2 * direction)
                return true;
        }
    }

    return false;
}

// Moves a piece and updates whether a capture was made
bool Board::makeMove(int x1, int y1, int x2, int y2, bool& wasCapture) {
    Piece* piece = grid[x1][y1];
    if (!piece) return false;

    char playerColor = piece->getColor();

    if (!isValidMove(x1, y1, x2, y2, playerColor)) {
        return false;
    }

    // Move the piece
    grid[x2][y2] = piece;
    grid[x1][y1] = nullptr;

    wasCapture = false;

    // Handle capture (if any)
    if (abs(x2 - x1) == 2 && abs(y2 - y1) == 2) {
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        delete grid[midX][midY];
        grid[midX][midY] = nullptr;
        wasCapture = true;
    }

    // Promote to king if reaching the back row
    if ((playerColor == 'r' && x2 == 7) || (playerColor == 'b' && x2 == 0)) {
        piece->promote();
    }

    return true;
}

// Checks if the player has any valid moves left
bool Board::hasAnyValidMoves(char playerColor) const {
    for (int x1 = 0; x1 < 8; ++x1) {
        for (int y1 = 0; y1 < 8; ++y1) {
            Piece* piece = grid[x1][y1];
            if (piece && piece->getColor() == playerColor) {
                for (int dx = -2; dx <= 2; ++dx) {
                    for (int dy = -2; dy <= 2; ++dy) {
                        int x2 = x1 + dx;
                        int y2 = y1 + dy;
                        if (isValidMove(x1, y1, x2, y2, playerColor)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Checks if a specific piece at (x, y) has a jump move available
bool Board::hasJumpAvailable(int x, int y) const {
    Piece* piece = grid[x][y];
    if (!piece) return false;

    char color = piece->getColor();
    int dirs[2] = { -1, 1 };  // diagonal directions

    for (int dx : dirs) {
        for (int dy : dirs) {
            int xMid = x + dx;
            int yMid = y + dy;
            int xDest = x + 2 * dx;
            int yDest = y + 2 * dy;

            // Check bounds and empty destination
            if (xDest >= 0 && xDest < 8 && yDest >= 0 && yDest < 8 &&
                grid[xDest][yDest] == nullptr) {

                Piece* midPiece = grid[xMid][yMid];
                if (midPiece && midPiece->getColor() != color) {
                    if (piece->getIsKing()) return true;
                    if (color == 'r' && dx == 1) return true;
                    if (color == 'b' && dx == -1) return true;
                }
            }
        }
    }
    return false;
}