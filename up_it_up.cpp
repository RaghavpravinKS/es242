#include <iostream>
#include <vector>
#include "queue.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;


vector<int> vert = {4, 1, 5, 3};

enum Direction { LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4};


int findIndex(const vector<int>& board, int value) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == value) {
            return i;
        }
    }
    return -1; // Value not found in the board
}

// Function to convert a board configuration to a unique identifier in base 7
int ord(const vector<int>& board) {

    int index = findIndex(board, 6);
    int mult_factor = pow(6,8);
    int uniqueIdentifier = index * mult_factor;

    int base = 1; // Base 6

    for (int i = board.size() - 1; i >= 0; --i) {
        if (i == index) continue;
        uniqueIdentifier += (board[i] * base);
        base *= 6;
    }
    return uniqueIdentifier;
}

// Function to print the board configuration in 3x3 format
void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; ++i) {
        cout << board[i] << " ";
        // Print a newline after every 3 entries
        if ((i + 1) % 3 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}



vector<int> left(vector<int>& board) {
    int index = findIndex(board, 6);

    if (index == 2 || index == 5 || index == 8) {
        return board;
    }

    int i = board[index+1];
    if (i >= 0 && i <= 3) {
        i = (i - 1 + 4) % 4;
    }
    vector<int> o = board;
    o[index+1] = 6;
    o[index] = i;

    return o;
}


vector<int> right(vector<int>& board) {
    int index = findIndex(board, 6);
    if (index == 0 || index == 3 || index == 6) {
        return board;
    }

    int i = board[index-1];
    if (i >= 0 && i <= 3) {
        i = (i + 1) % 4;
    }
    vector<int> o = board;
    o[index-1] = 6;
    o[index] = i;

    return o;

}


vector<int> up(vector<int>& board) {

    int index = findIndex(board, 6);
    if (index == 6 || index == 7 || index == 8) {
        return board;
    }
    int i = board[index+3];
    if (i == 5){
        i = 1;
    }
    else if (i == 4 || i == 1 || i == 3){
        i = vert[(i - 1 + 4) % 4];
    }
    vector<int> o = board;
    o[index+3] = 6;
    o[index] = i;

    return o;
}


vector<int> down(vector<int>& board) {

    const int index = findIndex(board, 6);
    if (index == 0 || index == 1 || index == 2) {
        return board;
    }
    int i = board[index-3];
    if (i == 5){
        i = 3;
    }
    else if (i == 4 || i == 1 || i == 3) {
        i = vert[(i + 1) % 4];
    }
    vector<int> o = board;
    o[index-3] = 6;
    o[index] = i;

    return o;

}


void performMoves(vector<int>& board, const string& moves) {
    for (char move : moves) {
        switch (move) {
            case 'L':
                cout << "Move LEFT\n" << endl;
                board = left(board);
                printBoard(board);
                break;
            case 'R':
                cout << "Move RIGHT\n" << endl;
                board = right(board);
                printBoard(board);
                break;
            case 'U':
                cout << "Move UP\n" << endl;
                board = up(board);
                printBoard(board);
                break;
            case 'D':
                cout << "Move DOWN\n" << endl;
                board = down(board);
                printBoard(board);
                break;
            default:
                // cout << "Invalid move: " << move << endl;
                // Handle invalid move if needed
                break;
        }
    }
}


vector<Direction> findPath(const vector<int>& src) {

    const vector<int> dest = {1, 1, 1, 1, 6, 1, 1, 1, 1};
    const int max_size = static_cast<int>(9 * pow(6, 8));
    queue<vector<int>, max_size> q;

    Direction visited[max_size];

    enqueue(q, src);
    visited[ord(src)] = LEFT;

    cout << "Processing..." << endl;
    cout << endl;

    while (!(q.len == 0)) {
        vector<int> u = dequeue(q);

        if (u == dest) {
            /* return the moves to get to u from src. */
            vector<Direction> moves;
            vector<int> c = u;
            int o = ord(c);
            while (!(c == src)) {
                moves.push_back(visited[o]);

                if (visited[o] == UP) {
                    c = down(c);
                }
                else if (visited[o] == DOWN) {
                    c = up(c);
                }
                else if (visited[o] == LEFT) {
                    c = right(c);
                }
                else if (visited[o] == RIGHT) {
                    c = left(c);
                }
                o = ord(c);
            }
            reverse(moves.begin(), moves.end());
            return moves;
        }

        vector<int> a = up(u);
        vector<int> b = down(u);
        vector<int> c = left(u);
        vector<int> d = right(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);
        int dord = ord(d);


        if (!visited[aord]) {
            visited[aord] = UP;
            enqueue(q, a);
            // printBoard(a);
        }


        if (!visited[bord]) {
            visited[bord] = DOWN;
            enqueue(q, b);
            // printBoard(b);
        }


        if (!visited[cord]) {
            visited[cord] = LEFT;
            enqueue(q, c);
            // printBoard(c);
        }


        if (!visited[dord]) {
            visited[dord] = RIGHT;
            enqueue(q, d);
            // printBoard(d);
        }

    }
    return vector<Direction> {LEFT, RIGHT, UP, DOWN};

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
    cout << "\nInitialized the board configuration:" << endl;
    printBoard(board);


    // Find the path
    vector<Direction> path = findPath(board);

    // Output the path if path exists. Trivial path is outputted by findPath if no path exists.
    if (path == vector<Direction> {LEFT, RIGHT, UP, DOWN}) {
        cout << "No path found." << endl;
    }
    else {

        cout << "Path found!" << endl;
        string path_seq;

        for (const auto& direction : path) {
            switch (direction) {
                case LEFT:
                    path_seq = path_seq + "L ";
                    break;
                case RIGHT:
                    path_seq = path_seq + "R ";
                    break;
                case UP:
                    path_seq = path_seq + "U ";
                    break;
                case DOWN:
                    path_seq = path_seq + "D ";
                    break;
            }

        }

        cout << endl;
        performMoves(board, path_seq);
        cout << "Path: " << path_seq << endl;
    }

    return 0;
}


/*
INDEXING OF CUBE FACES:
0: Left, 1: Front, 2: Right, 3: Back, 4: Top, 5: Bottom, 6: None
For each of the 9 positions in the board, enter the face index of the IITGN logo in the cube in that position. If empty, enter 6.
Cube 1: 0
Cube 2: 2
Cube 3: 1
Cube 4: 5
Cube 5: 4
Cube 6: 6
Cube 7: 1
Cube 8: 0
Cube 9: 5
Initialized the board configuration:
0 2 1
5 4 6
1 0 5

Path found!
Path: U R D D R U L
*/


/*
INDEXING OF CUBE FACES:
0: Left, 1: Front, 2: Right, 3: Back, 4: Top, 5: Bottom, 6: None
For each of the 9 positions in the board, enter the face index of the IITGN logo in the cube in that position. If empty, enter 6.
Cube 1: 0
Cube 2: 0
Cube 3: 0
Cube 4: 6
Cube 5: 1
Cube 6: 1
Cube 7: 1
Cube 8: 1
Cube 9: 1
Initialized the board configuration:
0 0 0
6 1 1
1 1 1

Path found!
Path: U L D D R U U L D D L U R R U L D R U L D D R U U L D L D R U
*/

/*
CCL Example Demonstration:

INDEXING OF CUBE FACES:
0: Left, 1: Front, 2: Right, 3: Back, 4: Top, 5: Bottom, 6: None
For each of the 9 positions in the board, enter the face index of the IITGN logo in the cube in that position. If empty, enter 6.
Cube 1: 3
Cube 2: 3
Cube 3: 3
Cube 4: 3
Cube 5: 6
Cube 6: 3
Cube 7: 3
Cube 8: 3
Cube 9: 3
Initialized the board configuration:
3 3 3
3 6 3
3 3 3


Path found!
Path: U L D R U R D L D R U L D L U U R D R U L D L U R D R U L L D R R D L U
*/


/*
INDEXING OF CUBE FACES:
0: Left, 1: Front, 2: Right, 3: Back, 4: Top, 5: Bottom, 6: None
For each of the 9 positions in the board, enter the face index of the IITGN logo in the cube in that position. If empty, enter 6.
Cube 1: 3
Cube 2: 3
Cube 3: 3
Cube 4: 3
Cube 5: 6
Cube 6: 3
Cube 7: 3
Cube 8: 3
Cube 9: 3

Initialized the board configuration:
3 3 3
3 6 3
3 3 3

Processing...

Path found!

Move UP

3 3 3
3 5 3
3 6 3

Move LEFT

3 3 3
3 5 3
3 2 6

Move DOWN

3 3 3
3 5 6
3 2 4

Move RIGHT

3 3 3
3 6 5
3 2 4

Move UP

3 3 3
3 2 5
3 6 4

Move RIGHT

3 3 3
3 2 5
6 0 4

Move DOWN

3 3 3
6 2 5
4 0 4

Move LEFT

3 3 3
1 6 5
4 0 4

Move DOWN

3 6 3
1 4 5
4 0 4

Move RIGHT

6 0 3
1 4 5
4 0 4

Move UP

4 0 3
6 4 5
4 0 4

Move LEFT

4 0 3
4 6 5
4 0 4

Move DOWN

4 6 3
4 0 5
4 0 4

Move LEFT

4 2 6
4 0 5
4 0 4

Move UP

4 2 1
4 0 6
4 0 4

Move UP

4 2 1
4 0 3
4 0 6

Move RIGHT

4 2 1
4 0 3
4 6 1

Move DOWN

4 2 1
4 6 3
4 0 1

Move RIGHT

4 2 1
6 4 3
4 0 1

Move UP

4 2 1
3 4 3
6 0 1

Move LEFT

4 2 1
3 4 3
3 6 1

Move DOWN

4 2 1
3 6 3
3 1 1

Move LEFT

4 2 1
3 2 6
3 1 1

Move UP

4 2 1
3 2 4
3 1 6

Move RIGHT

4 2 1
3 2 4
3 6 2

Move DOWN

4 2 1
3 6 4
3 2 2

Move RIGHT

4 2 1
6 0 4
3 2 2

Move UP

4 2 1
5 0 4
6 2 2

Move LEFT

4 2 1
5 0 4
1 6 2

Move LEFT

4 2 1
5 0 4
1 1 6

Move DOWN

4 2 1
5 0 6
1 1 1

Move RIGHT

4 2 1
5 6 1
1 1 1

Move RIGHT

4 2 1
6 5 1
1 1 1

Move DOWN

6 2 1
1 5 1
1 1 1

Move LEFT

1 6 1
1 5 1
1 1 1

Move UP

1 1 1
1 6 1
1 1 1

Path: U L D R U R D L D R U L D L U U R D R U L D L U R D R U L L D R R D L U
*/
