#include <iostream>
#include <vector>

using namespace std;


vector<int> vert = {4, 1, 5, 3};

enum Direction { LEFT, RIGHT, UP, DOWN };


// Function to print the board configuration in 3x3 format
void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; ++i) {
        cout << board[i] << " ";
        // Print a newline after every 3 entries
        if ((i + 1) % 3 == 0) {
            cout << endl;
        }
    }
}


int left(int i) {
    if (i >= 0 && i <= 3) {
        i = (i - 1 + 4) % 4;
    }
    return i;
}


int right(int i) {
    if (i >= 0 && i <= 3) {
        i = (i + 1) % 4;
    }
    return i;
}


int up(int i) {
    i = vert[(i - 1 + 4) % 4];
    return i;
}


int down(int i) {
    i = vert[(i + 1) % 4];
    return i;
}

int findIndex(const vector<int>& board, int value) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == value) {
            return i;
        }
    }
    return -1; // Value not found in the board
}

vector<Direction> findPath(vector<int> board, vector<Direction> path) {
    if (board == {1,1,1,1,6,1,1,1,1}){
        return path;
    }

    int bi = findIndex(board, 6);

    if (bi == -1) {
        cout << "Target value not found in the board." << endl;
        return path;
    }


    int child_indices[4] = [bi-1, bi+1, bi-3, bi+3];
    int rotated_indices[4] = {left(board[bi+1]), right(board[bi-1]), down(board[bi-3]), up(board[bi+3])};

    for (int j = 0; j < 4; ++j) {
        if (0 <= child_indices[j] && child_indices[j] << 8 ) {
            path.push_back(static_cast<Direction>(j));
            board[bi] = rotated_indices[j];
            board[child_indices[j] = 6;

            return findPath(board, path);


            // Undo the move
            board[moves[j]] = board[i];
            board[i] = 6;
            path.pop_back();
        }
    }

    return path;
}


int main() {

    // Initialize a vector with size 9
    vector<int> board(9);

    // Take input for each element of the board
    cout << "INDEXING OF CUBE FACES:\n0: Left, 1: Front, 2: Right, 3: Back, 4: Top, 5: Bottom, 6: None" << endl;
    cout << "For each of the 9 positions in the board, enter the face index of the IITGN logo in the cube in that position. If empty, enter 6." << endl;

    for (int i = 0; i < 9; ++i) {
        cout << "Cube " << i + 1 << ": ";
        cin >> board[i];

        // Validate input (between 0 and 6)
        while (board[i] < 0 || board[i] > 6) {
            cout << "Invalid input! Please enter an integer between 0 and 6: ";
            cin >> board[i];
        }
    }

    // Print the initialized board
    cout << "Initialized the board configuration:" << endl;
    printBoard(board);

    // Vector to store the movement directions (L, R, U, D)
    vector<Direction> path;

    // Find the path and modify the board configuration
    bool pathFound = findPath(board, path, startIndex);

    // Output the modified board and path
    if (pathFound) {
        cout << "Path found! Modified Board Configuration:" << endl;
        printBoard(board);

        cout << "Path: ";
        for (const auto& direction : path) {
            switch (direction) {
                case LEFT:
                    cout << "L ";
                    break;
                case RIGHT:
                    cout << "R ";
                    break;
                case UP:
                    cout << "U ";
                    break;
                case DOWN:
                    cout << "D ";
                    break;
            }
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
