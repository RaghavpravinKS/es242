#include <iostream>
#include <vector>
#include "queue.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;


vector<int> vert = {4, 1, 5, 3};

enum Direction { LEFT, RIGHT, UP, DOWN };


// Function to convert a board configuration to a unique identifier in base 7
int ord(const vector<int>& board) {
    int uniqueIdentifier = 0;
    int base = 1; // Base 7
    for (int i = board.size() - 1; i >= 0; --i) {
        uniqueIdentifier += (board[i] * base);
        base *= 7;
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
}

int findIndex(const vector<int>& board, int value) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == value) {
            return i;
        }
    }
    return -1; // Value not found in the board
}


vector<int> left(vector<int>& board) {
    int index = findIndex(board, 6);

    if (!(index == 2 || index == 5 || index == 8)) {
        int i = board[index+1];
        if (i >= 0 && i <= 3) {
            i = (i - 1 + 4) % 4;
        }
        vector<int> o = board;
        o[index+1] = 6;
        o[index] = i;

        return o;
    }
    else {
        return {0};
    }
}


vector<int> right(vector<int>& board) {
    int index = findIndex(board, 6);
    if (!(index == 0 || index == 3 || index == 6)) {
        int i = board[index-1];
        if (i >= 0 && i <= 3) {
            i = (i + 1) % 4;
        }
        vector<int> o = board;
        o[index-1] = 6;
        o[index] = i;

        return o;
    }
    else {
        return {0};
    }
}


vector<int> up(vector<int>& board) {

    int index = findIndex(board, 6);
    if (!(index == 6 || index == 7 || index == 8)) {
        int i = board[index+3];
        if (i == 5){
            i = 1;
        }
        else{
            i = vert[(i - 1 + 4) % 4];
        }
        vector<int> o = board;
        o[index+3] = 6;
        o[index] = i;

        return o;
    }
    else {
        return {0};
    }
}


vector<int> down(vector<int>& board) {

    int index = findIndex(board, 6);
    if (!(index == 0 || index == 1 || index == 2)) {
        int i = board[index-3];
        if (i == 5){
            i = 3;
        }
        else {
            i = vert[(i + 1) % 4];
        }
        vector<int> o = board;
        o[index-3] = 6;
        o[index] = i;

        return o;
    }
    else {
        return {0};
    }

}


vector<Direction> findPath(vector<int> src) {

    vector<int> dest = {1,1,1,1,6,1,1,1,1};
    const int max_size = static_cast<int>(pow(7, 9));
    queue<vector<int>, max_size> q;

    Direction visited[max_size];
    vector<int> parent[max_size];


    enqueue(q, src);
    // visited[ord(src)] = LEFT;

    cout << endl;

    while (!(q.len == 0)) {
        vector<int> u = dequeue(q);
//        cout << "Popping from the queue:\n";
//        printBoard(u);
//        cout << endl;


        if (u == dest) {
            /* return the moves to get to u from src. */
            vector<Direction> moves;
            vector<int> c = u;
            int o = ord(c);
            while (!(c == src)) {
                moves.push_back(visited[o]);
                c = parent[o];
                o = ord(c);
            }
            reverse(moves.begin(), moves.end());
            return moves;
        }

        int index = findIndex(u, 6);
        vector<int> err = {0};

        if (!(visited[ord(u)] == DOWN)){
            vector<int> a = up(u);
            if (!(a == err)){
                int aord = ord(a);
                if (!visited[aord]) {
                    visited[aord] = UP;
                    parent[aord] = u;
                    enqueue(q, a);
    //                cout << "UP: Adding to the queue:\n";
    //                printBoard(a);
    //                cout << endl;
                }
            }
        }

        if (!(visited[ord(u)] == UP)){
            vector<int> b = down(u);
            if (!(b == err)){
                int bord = ord(b);
                if (!visited[bord]) {
                    visited[bord] = DOWN;
                    parent[bord] = u;
                    enqueue(q, b);
    //                cout << "DOWN: Adding to the queue:\n";
    //                printBoard(b);
    //                cout << endl;
                }
            }
        }

        if (!(visited[ord(u)] == RIGHT)){
            vector<int> c = left(u);
            if (!(c == err)){
                int cord = ord(c);
                if (!visited[cord]) {
                    visited[cord] = LEFT;
                    parent[cord] = u;
                    enqueue(q, c);
    //                cout << "LEFT: Adding to the queue:\n";
    //                printBoard(c);
    //                cout << endl;
                }
            }
        }

        if (!(visited[ord(u)] == LEFT)){
            vector<int> d = right(u);
            if (!(d == err)){
                int dord = ord(d);
                if (!visited[dord]) {
                    visited[dord] = RIGHT;
                    parent[dord] = u;
                    enqueue(q, d);
    //                cout << "RIGHT: Adding to the queue:\n";
    //                printBoard(d);
    //                cout << endl;
                }
            }
        }
    }
    assert(0);

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



    // Find the path and modify the board configuration
    vector<Direction> path = findPath(board);

    // Output the modified board and path
    if (true) {
        cout << "Path found!" << endl;

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
