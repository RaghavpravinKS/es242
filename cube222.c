#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

char solved_cube[2][4][3] = {
    {
        {'W','G','O'},
        {'W','O','B'},
        {'W','R','G'},
        {'W','B','R'}
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

void read_board(cube* s)
{
    char v;
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int e = 0; e < 3; ++e){
                scanf(" %c", &v);
                s->b[r][c][e] = v;
            }
        }
    }
}

bool areEqual(char arr1[], char arr2[]) {
    int freq1[256] = {0};
    int freq2[256] = {0};

    // Calculate frequency of each character in arr1
    for (int i = 0; i < 3; i++) {
        freq1[arr1[i]]++;
    }

    // Calculate frequency of each character in arr2
    for (int i = 0; i < 3; i++) {
        freq2[arr2[i]]++;
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

bool is_valid(const cube* s)
{
    int sum = 0;
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            char corner_piece[4]; // increased size to accommodate null character
            for (int e = 0; e < 3; ++e) {
                corner_piece[e] = s->b[r][c][e];
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
                        printCharArray(corner_piece);
                        printCharArray(orig_piece);
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
    printf("Sum: %d\n", sum);
    return sum % 3 == 0;
}

void print_board(const cube* s)
{
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int e = 0; e < 3; ++e) {
                char v = s->b[r][c][e];
                printf("%c",v);
            }
        printf(" ");
        }
    printf("\n");
    }
}

int main()
{
    cube s;
    read_board(&s);
    if (is_valid(&s)){
        printf("The cube is solvable.\n");
    } else{
        printf("The cube is unsolvable.\n");
    }
    print_board(&s);
}