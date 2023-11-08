#include <iostream>
#include <vector>
#include "queue.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>

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

    return a % 500007;
}

struct cube_det
{
    cube parent ;
    string move ;
    int visited = 0 ;
    int ord_ = -1;
    cube state ;
};

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

vector<vector<cube_det>> hash_table(500010);

cube_det hash_function(int ord_a,const cube& c) {
    auto a = hash_table[ord_a];

    for (int i = 0 ; i < a.size() ; i ++){
        if (same(c,a[i].state)){return a[i] ;}
    }

    return {c,"", 0, -1};
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

vector<string> solve(const cube& s){
    queue<cube, fact(10)> q ;
    cube c = s ;
    enqueue(q, c) ;
    int c_ord = ord(c) ;
    hash_table[c_ord].push_back(cube_det{c, "", 1,c_ord,c}) ;

    while (q.len != 0) {
        cube u = dequeue(q);
        if (is_solved(u)){
            vector<string> moves ;
            cube c_ = u ;
            int c_s = ord(c_) ;
            auto store = hash_function(c_s,c_) ;
            while (!same(s,c_)){
                moves.push_back(store.move) ;
                c_ = store.parent ;
                c_s = ord(c_) ;
                store = hash_function(c_s,c_) ;
            }
            reverse(moves.begin(),moves.end()) ;
            return moves ;

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

        int uni_R = ord(R) ;
        int uni_U = ord(U) ;
        int uni_F = ord(F) ;
        int uni_R1 = ord(R1) ;
        int uni_U1 = ord(U1) ;
        int uni_F1 = ord(F1) ;
        int uni_R2 = ord(R2) ;
        int uni_U2 = ord(U2) ;
        int uni_F2 = ord(F2) ;

        if (!hash_function(uni_R,R).visited){
            hash_table[uni_R].push_back(cube_det{u, "R", 1,uni_R,R}) ;
            enqueue(q, R);
        }

        if (!hash_function(uni_U,U).visited){
            hash_table[uni_U].push_back(cube_det{u, "U", 1,uni_U,U}) ;
            enqueue(q, U);
        }

        if (!hash_function(uni_F,F).visited){
            hash_table[uni_F].push_back(cube_det{u, "F", 1,uni_F,F}) ;
            enqueue(q, F);
        }

        if (!hash_function(uni_R1,R1).visited){
            hash_table[uni_R1].push_back(cube_det{u, "R'", 1,uni_R1,R1}) ;
            enqueue(q, R1);
        }

        if (!hash_function(uni_U1,U1).visited){
            hash_table[uni_U1].push_back(cube_det{u, "U'", 1,uni_U1,U1}) ;
            enqueue(q, U1);
        }

        if (!hash_function(uni_F1,F1).visited){
            hash_table[uni_F1].push_back(cube_det{u, "F'", 1,uni_F1,F1}) ;
            enqueue(q, F1);
        }
        if (!hash_function(uni_R2,R2).visited){
            hash_table[uni_R2].push_back(cube_det{u, "2R", 1,uni_R2,R2}) ;
            enqueue(q, R2);
        }
        if (!hash_function(uni_U2,U2).visited){
            hash_table[uni_U2].push_back(cube_det{u, "2U", 1,uni_U2,U2}) ;
            enqueue(q, U2);
        }
        if (!hash_function(uni_F2,F2).visited){
            hash_table[uni_F2].push_back(cube_det{u, "2F", 1,uni_F2,F2}) ;
            enqueue(q, F2);
        }
    }

    assert(0) ;
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

// solved configuration
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

// single step configuration
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

// sample input
/*
R
Y
G
B
Y
R
W
O
B
G
Y
O
B
O
Y
R
G
W
W
G
O
B
R
W
*/