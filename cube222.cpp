#include <iostream>
#include <vector>
#include "queue.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>
// #include<queue>
using namespace std;

char solved_cube[2][4][3] = {
        {
                {'W','G','O'},
                {'W','O','B'},
                {'W','B','R'},
                {'W','R','G'}
        },
        {
                {'Y','B','O'},
                {'Y','O','G'},
                {'Y','G','R'},
                {'Y','R','B'}
        }
};

typedef struct {
    char b[2][4][3];
} cube;

constexpr int fact(int i)
{
    int p = 1;
    for (int j = 2; j <= i; ++j) {
        p *= j;
    }
    return p;
}

long long ord(const cube& s)
{
    long long a = 0;
    long long base = 1;

    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int e = 0; e < 3; ++e) {  
                int digit = s.b[r][c][e] - 'A';
                a += digit * base;
                base *= 3;
            }
        }
    }

    return a;
}

void read_cube(cube& s)
{
    char v;
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int e = 0; e < 3; ++e){
                scanf(" %c", &v);
                s.b[r][c][e] = v;
            }
        }
    }
}

bool areEqual(char arr1[], char arr2[]) {
    int freq1[256] = {0};
    int freq2[256] = {0};

    // Calculate frequency of each character in arr1
    for (int i = 0; i < 3; i++) {
        freq1[(unsigned char)arr1[i]]++;
    }

    // Calculate frequency of each character in arr2
    for (int i = 0; i < 3; i++) {
        freq2[(unsigned char)arr2[i]]++;
    }

    // Compare the frequency of characters
    for (int i = 0; i < 256; i++) {
        if (freq1[i] != freq2[i]) {
            return false;
        }
    }

    return true;
}

void printCharArray(char arr[]) {
    int i = 0;
    while(arr[i] != '\0' && i<3) { // added condition to prevent reading beyond array bounds
        printf("%c ", arr[i]);
        i++;
    }
    printf("\n");
}

bool is_valid(const cube& s)
{
    int sum = 0;
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            char corner_piece[4]; // increased size to accommodate null character
            for (int e = 0; e < 3; ++e) {
                corner_piece[e] = s.b[r][c][e];
            }
            corner_piece[3] = '\0'; // add null character to end of string
            for (int ro = 0; ro < 2; ++ro) {
                for (int co = 0; co < 4; ++co) {
                    char orig_piece[4]; // increased size to accommodate null character
                    for (int el = 0; el < 3; ++el) {
                        orig_piece[el] = solved_cube[ro][co][el];
                    }
                    orig_piece[3] = '\0'; // add null character to end of string
                    if (areEqual(corner_piece, orig_piece))
                    {
                        // printCharArray(corner_piece);
                        // printCharArray(orig_piece);
                        if (corner_piece[0] == orig_piece[2]){
                            sum += 1;
                        }
                        else if (corner_piece[1] == orig_piece[2]){
                            sum += 2;
                        }
                    }
                }
            }
        }
    }
    // printf("Sum: %d\n", sum);
    return sum % 3 == 0;
}

void print_cube(const cube& s)
{
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int e = 0; e < 3; ++e) {
                char v = s.b[r][c][e];
                printf("%c",v);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

void clock(char arr[3]) {
    std::swap(arr[0], arr[2]);
    std::swap(arr[0], arr[1]);
}

void anti_clock(char arr[3]) {
    std::swap(arr[0], arr[1]);
    std::swap(arr[0], arr[2]);
}

cube right(const cube& c)
{
    cube s = c;
    char f1[3] = {s.b[0][1][0], s.b[0][1][1], s.b[0][1][2]};
    char f2[3] = {s.b[0][2][0], s.b[0][2][1], s.b[0][2][2]};
    char b1[3] = {s.b[1][0][0], s.b[1][0][1], s.b[1][0][2]};
    char b2[3] = {s.b[1][3][0], s.b[1][3][1], s.b[1][3][2]};
    clock(f1);
    anti_clock(f2);
    clock(b2);
    anti_clock(b1);
    for (int i = 0; i < 3; ++i) {
        s.b[0][1][i] = f2[i];
        s.b[0][2][i] = b2[i];
        s.b[1][0][i] = f1[i];
        s.b[1][3][i] = b1[i];
    }
    return s;
}

cube up(const cube& c)
{
    cube s = c;    
    char f1[3] = {s.b[0][0][0], s.b[0][0][1], s.b[0][0][2]};
    char f2[3] = {s.b[0][1][0], s.b[0][1][1], s.b[0][1][2]};
    char b1[3] = {s.b[1][0][0], s.b[1][0][1], s.b[1][0][2]};
    char b2[3] = {s.b[1][1][0], s.b[1][1][1], s.b[1][1][2]};
    clock(f1);
    anti_clock(f2);
    anti_clock(b2);
    clock(b1);
    for (int i = 0; i < 3; ++i) {
        s.b[0][0][i] = f2[i];
        s.b[0][1][i] = b1[i];
        s.b[1][0][i] = b2[i];
        s.b[1][1][i] = f1[i];
    }
    return s;
}

cube front(const cube& c)
{
    cube s = c;
    char f1[3] = {s.b[0][0][0], s.b[0][0][1], s.b[0][0][2]};
    char f2[3] = {s.b[0][1][0], s.b[0][1][1], s.b[0][1][2]};
    char f3[3] = {s.b[0][2][0], s.b[0][2][1], s.b[0][2][2]};
    char f4[3] = {s.b[0][3][0], s.b[0][3][1], s.b[0][3][2]};
    for (int i = 0; i < 3; ++i) {
        s.b[0][0][i] = f4[i];
        s.b[0][1][i] = f1[i];
        s.b[0][2][i] = f2[i];
        s.b[0][3][i] = f3[i];
    }
    return s;
}

cube right1(const cube& c)
{
    cube s = c;
    char f1[3] = {s.b[0][1][0], s.b[0][1][1], s.b[0][1][2]};
    char f2[3] = {s.b[0][2][0], s.b[0][2][1], s.b[0][2][2]};
    char b1[3] = {s.b[1][0][0], s.b[1][0][1], s.b[1][0][2]};
    char b2[3] = {s.b[1][3][0], s.b[1][3][1], s.b[1][3][2]};
    clock(f1);
    anti_clock(f2);
    clock(b2);
    anti_clock(b1);
    for (int i = 0; i < 3; ++i) {
        s.b[0][1][i] = b1[i];
        s.b[0][2][i] = f1[i];
        s.b[1][0][i] = b2[i];
        s.b[1][3][i] = f2[i];
    }
    return s;
}

cube up1(const cube& c)
{
    cube s = c;
    char f1[3] = {s.b[0][0][0], s.b[0][0][1], s.b[0][0][2]};
    char f2[3] = {s.b[0][1][0], s.b[0][1][1], s.b[0][1][2]};
    char b1[3] = {s.b[1][0][0], s.b[1][0][1], s.b[1][0][2]};
    char b2[3] = {s.b[1][1][0], s.b[1][1][1], s.b[1][1][2]};
    clock(f1);
    anti_clock(f2);
    anti_clock(b2);
    clock(b1);
    for (int i = 0; i < 3; ++i) {
        s.b[0][0][i] = b2[i];
        s.b[0][1][i] = f1[i];
        s.b[1][0][i] = f2[i];
        s.b[1][1][i] = b1[i];
    }
    return s;
}

cube front1(const cube& c)
{
    cube s = c;
    char f1[3] = {s.b[0][0][0], s.b[0][0][1], s.b[0][0][2]};
    char f2[3] = {s.b[0][1][0], s.b[0][1][1], s.b[0][1][2]};
    char f3[3] = {s.b[0][2][0], s.b[0][2][1], s.b[0][2][2]};
    char f4[3] = {s.b[0][3][0], s.b[0][3][1], s.b[0][3][2]};
    for (int i = 0; i < 3; ++i) {
        s.b[0][0][i] = f2[i];
        s.b[0][1][i] = f3[i];
        s.b[0][2][i] = f4[i];
        s.b[0][3][i] = f1[i];
    }
    return s;
}

cube front2(const cube& c)
{
    cube s = c;
    s = front(s);
    return front(s);
}

cube up2(const cube& c)
{
    cube s = c;
    s = up(s);
    return up(s);
}

cube right2(const cube& c)
{
    cube s = c;
    s = right(s);
    return right(s);
}

bool is_solved(const cube &s)
{
    if ((s.b[0][0][0] == s.b[0][1][0] && s.b[0][1][0] == s.b[0][2][0] && s.b[0][2][0] == s.b[0][3][0]) && 
        (s.b[1][0][0] == s.b[1][1][0] && s.b[1][1][0] == s.b[1][2][0] && s.b[1][2][0] == s.b[1][3][0])){
        if ((s.b[0][0][1] == s.b[0][3][2]) && (s.b[0][0][2] == s.b[0][1][1]) && 
            (s.b[0][1][2] == s.b[0][2][1]) && (s.b[0][2][2] == s.b[0][3][1])){
            if ((s.b[1][0][1] == s.b[1][3][2]) && (s.b[1][0][2] == s.b[1][1][1]) && 
                (s.b[1][1][2] == s.b[1][2][1]) && (s.b[1][2][2] == s.b[1][3][1])){
                if ((s.b[0][0][1] == s.b[1][1][2]) && (s.b[0][1][2] == s.b[1][0][1])){
                    return true;
                }
                else{
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/*
string to_string(const cube& s) {
    string st = "";
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int e = 0; e < 3; ++e){
                    st += s.b[r][c][e];
            }
        }
    }
    return st;
}
*/
bool same(const cube& s, cube& h){
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int e = 0; e < 3; ++e){
                if (s.b[r][c][e] != h.b[r][c][e]){
                    return false;
                }
            }
        }
    }
    return true;
}
/*
vector<string> solve(const cube& s)
{
    queue<cube, fact(10)> q;
    map <string , int> visited;
    cube c = s;
    enqueue(q, c);
    visited[to_string(c)] = 1;

    map <string , cube> parent;
    map <string , string> move;

    while (q.len != 0) {
        cube u = dequeue(q);

        if (is_solved(u)){
            vector<string> moves;
            cube t = u;
            string o = to_string(t);
            while (!same(s,t)){
                moves.push_back(move[o]);
                t = parent[o];
                o = to_string(t);
            }
            reverse(moves.begin(),moves.end());
            return moves;

        }

        cube R = right(u);
        cube U = up(u);
        cube F = front(u);
        cube R1 = right1(u);
        cube U1 = up1(u);
        cube F1 = front1(u);
        cube R2 = right2(u);
        cube U2 = up2(u);
        cube F2 = front2(u);
        
        string s_R = to_string(right(u));
        string s_U = to_string(up(u));
        string s_F = to_string(front(u));
        string s_R1 = to_string(right1(u));
        string s_U1 = to_string(up1(u));
        string s_F1 = to_string(front1(u));
        string s_R2 = to_string(right2(u));
        string s_U2 = to_string(up2(u));
        string s_F2 = to_string(front2(u));
        
        if (!visited[s_R]){
            visited[s_R] = 1;
            move[s_R] = "R";
            parent[s_R] = u;
            enqueue(q, R);
        }
        if (!visited[s_U]){
            visited[s_U] = 1;
            move[s_U] = "U";
            parent[s_U] = u;
            enqueue(q, U);
        }
        if (!visited[s_F]){
            visited[s_F] = 1;
            move[s_F] = "F";
            parent[s_F] = u;
            enqueue(q, F);
        }
        if (!visited[s_R1]){
            visited[s_R1] = 1;
            move[s_R1] = "R'";
            parent[s_R1] = u;
            enqueue(q, R1);
        }
        if (!visited[s_U1]){
            visited[s_U1] = 1;
            move[s_U1] = "U'";
            parent[s_U1] = u;
            enqueue(q, U1);
        }
        if (!visited[s_F1]){
            visited[s_F1] = 1;
            move[s_F1] = "F'";
            parent[s_F1] = u;
            enqueue(q, F1);
        }
        if (!visited[s_R2]){
            visited[s_R2] = 1;
            move[s_R2] = "2R";
            parent[s_R2] = u;
            enqueue(q, R2);
        }
        if (!visited[s_U2]){
            visited[s_U2] = 1;
            move[s_U2] = "2U";
            parent[s_U2] = u;
            enqueue(q, U2);
        }
        if (!visited[s_F2]){
            visited[s_F2] = 1;
            move[s_F2] = "2F";
            parent[s_F2] = u;
            enqueue(q, F2);
        }                        
    }
    assert(0);
}
*/
vector<string> solve(const cube& s)
{
    queue<cube, fact(10)> q;
    set<long long> visited; // Use a set to store visited configurations as long long integers
    cube c = s;
    enqueue(q, c);
    visited.insert(ord(c));

    unordered_map<long long, cube> parent; // Use unordered_map to store parent configurations
    unordered_map<long long, string> move; // Use unordered_map to store moves

    while (q.len != 0) {
        cube u = dequeue(q);

        if (is_solved(u)){
            vector<string> moves;
            cube t = u;
            while (!same(s,t)){
                moves.push_back(move[ord(t)]);
                t = parent[ord(t)];
            }
            reverse(moves.begin(),moves.end());
            return moves;
        }

        cube R = right(u);
        cube U = up(u);
        cube F = front(u);
        cube R1 = right1(u);
        cube U1 = up1(u);
        cube F1 = front1(u);
        cube R2 = right2(u);
        cube U2 = up2(u);
        cube F2 = front2(u);

        if (visited.find(ord(R)) == visited.end()){
            visited.insert(ord(R));
            move[ord(R)] = "R";
            parent[ord(R)] = u;
            enqueue(q, R);
        }
        if (visited.find(ord(U)) == visited.end()){
            visited.insert(ord(U));
            move[ord(U)] = "U";
            parent[ord(U)] = u;
            enqueue(q, U);
        }
        if (visited.find(ord(F)) == visited.end()){
            visited.insert(ord(F));
            move[ord(F)] = "F";
            parent[ord(F)] = u;
            enqueue(q, F);
        }
        if (visited.find(ord(R1)) == visited.end()){
            visited.insert(ord(R1));
            move[ord(R1)] = "R'";
            parent[ord(R1)] = u;
            enqueue(q, R1);
        }
        if (visited.find(ord(U1)) == visited.end()){
            visited.insert(ord(U1));
            move[ord(U1)] = "U'";
            parent[ord(U1)] = u;
            enqueue(q, U1);
        }
        if (visited.find(ord(F1)) == visited.end()){
            visited.insert(ord(F1));
            move[ord(F1)] = "F'";
            parent[ord(F1)] = u;
            enqueue(q, F1);
        }
        if (visited.find(ord(R2)) == visited.end()){
            visited.insert(ord(R2));
            move[ord(R2)] = "2R";
            parent[ord(R2)] = u;
            enqueue(q, R2);
        }
        if (visited.find(ord(U2)) == visited.end()){
            visited.insert(ord(U2));
            move[ord(U2)] = "2U";
            parent[ord(U2)] = u;
            enqueue(q, U2);
        }
        if (visited.find(ord(F2)) == visited.end()){
            visited.insert(ord(F2));
            move[ord(F2)] = "2F";
            parent[ord(F2)] = u;
            enqueue(q, F2);
        }                        
    }
    assert(0);
}

int main()
{
    cube s;
    printf("The pocket cube has the following colours: White (W), Yellow (Y), Blue (B), Green (G), Red (R) & Orange (O)\n");
    printf("For each cubelet, input the colour sequence in clockwise manner:\n");
    read_cube(s);
    if (is_valid(s)){
        printf("The cube is solvable.\n");
        printf("The initial cube configuration is:\n\n");
        print_cube(s);
        if (is_solved(s)){
            printf("...and the cube is solved.\n");
        }
        else{
            printf("...and the cube is not solved. So here are the moves to solve it!\n");
            auto moves = solve(s);
            for (auto& i : moves){cout << i << ' ';}
            cout << "\n";
        }
    } else{
        printf("The cube is unsolvable.\n");
    }
}

/*
R
G
W
R
W
B
R
B
Y
R
Y
G
O
B
W
O
W
G
O
G
Y
O
Y
B
*/

/*
R
Y
G
R
G
W
R
W
B
R
B
Y
O
B
W
O
W
G
O
G
Y
O
Y
B
*/
