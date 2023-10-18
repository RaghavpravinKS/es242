#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum {
    EMPTY = 0,
    RED,
    BLUE,
};

#define ROW (4)
#define COLUMN (5)
#define WIN (4)
#define ANSI_COLOR_RED "\x1b[31;1m"
#define ANSI_COLOR_BLUE "\x1b[1;34m"
#define ANSI_COLOR_GREEN "\x1b[32;1m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef char player_t;
typedef char board_t[ROW][COLUMN];

void init_board(board_t board)
{
    for (int row = 0; row < ROW; ++row)
    {
        for (int col = 0; col < COLUMN; ++col)
        {
            board[row][col] = '.';
        }
    }
}

void print_board(board_t board)
{
    for (int row = 0; row < ROW; ++row)
    {
        for (int col = 0; col < COLUMN; ++col)
        {
            // printf("%c ", board[row][col]);
            if (board[row][col]=='R'){
                printf("%sR %s",            
                    ANSI_COLOR_RED, ANSI_COLOR_RESET);
            } else if (board[row][col] == 'B') {
                printf("%sB %s",            
                    ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
            } else {
                printf("%s. %s",            
                    ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
            }
        }
        printf("\n");
    }
}

void print_keys(board_t board)
{
    for (int i = 0; i < COLUMN; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");
}

int is_full(board_t board)
{
    for (int row = 0; row < ROW; ++row)
    {
        for (int col = 0; col < COLUMN; ++col)
        {
            if (board[row][col] == '.')
            {
                return 0;
            }
        }
    }
    return 1;
}

typedef struct
{
    char to_check;
    int score;
} player_count;

typedef struct
{
    int row;
    int col;
} place_XO;

typedef struct
{
    int row;
    int col;
    int score;
} move_t;

int place_move(board_t board, player_t player, place_XO place_object)
{
    int placed = 0;
    for (int row = ROW - 1; row >= 0; row--)
    {
        if (board[row][place_object.col] == '.')
        {
            board[row][place_object.col] = player;
            placed = 1;
            return row;
        }
    }
    if (placed == 0)
    {
        return -1;
    }
}

int has_won(board_t board, player_t player)
{
    player_count count;
    count.to_check = player;
    count.score = 0;
    for (int row = 0; row < ROW; ++row)
    {
        for (int col = 0; col < COLUMN; ++col)
        {
            if (count.to_check == board[row][col])
            {
                count.score++;
            }
            else
            {
                count.score = 0;
            }
            if (count.score >= WIN)
            {
                return 1;
            }
        }
        count.score = 0;
    }
    count.score = 0;
    for (int col = 0; col < COLUMN; ++col)
    {
        for (int row = 0; row < ROW; ++row)
        {
            if (count.to_check == board[row][col])
            {
                count.score++;
            }
            else
            {
                count.score = 0;
            }
            if (count.score >= WIN)
            {
                return 1;
            }
        }
        count.score = 0;
    }
    count.score = 0;
    for (int start_row = 0; start_row <= ROW - WIN; ++start_row)
    {
        for (int start_col = 0; start_col <= COLUMN - WIN; ++start_col)
        {
            int cd1 = 0, cd2 = 0;
            for (int i = 0; i < WIN; ++i)
            {
                if (board[start_row + i][start_col + i] == player)
                {
                    cd1++;
                    if (cd1 == WIN)
                    {
                        return 1;
                    }
                }
                else
                {
                    cd1 = 0;
                }

                if (board[start_row + i][start_col + WIN - 1 - i] == player)
                {
                    cd2++;
                    if (cd2 == WIN)
                    {
                        return 1;
                    }
                }
                else
                {
                    cd2 = 0;
                }
            }
        }
    }
    return 0;
}

player_t other_player(player_t player)
{
    switch (player)
    {
    case 'R':
        return 'B';
    case 'B':
        return 'R';
    default:
        assert(0);
    }
}

move_t best_move(board_t board, player_t player, int v)
{
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));
    for (int col = 0; col < COLUMN; ++col)
    {
        place_XO move;
        move.row = ROW - 1;
        move.col = col;
        move.row = place_move(board, player, move);
        if (has_won(board, player))
        {
            board[move.row][move.col] = '.';
            return (move_t){
                .row = move.row,
                .col = move.col,
                .score = 1};
        }
        board[move.row][col] = '.';
    }
    for (int col = 0; col < COLUMN; ++col)
    {
        int row = ROW - 1;
        while (row > 0 && board[row][col] != '.')
        {
            row--;
        };
        if (board[row][col] == '.' && row >= 0)
        {
            board[row][col] = player;
            if (is_full(board))
            {
                board[row][col] = '.';
                return (move_t){
                    .row = row,
                    .col = col,
                    .score = 0};
            }
            response = best_move(board, other_player(player), v + 1);
            board[row][col] = '.';
            if (v > 13)
            {
                return (move_t){
                    .row = row,
                    .col = col,
                    .score = 1,
                };
            }
            if (response.score == -1)
            {
                return (move_t){
                    .row = row,
                    .col = col,
                    .score = 1,
                };
            }
            else if (response.score == 0)
            {
                candidate = (move_t){
                    .row = row,
                    .col = col,
                    .score = 0};
                no_candidate = 0;
            }
            else
            {
                if (no_candidate)
                {
                    candidate = (move_t){
                        .row = row,
                        .col = col,
                        .score = -1};
                    no_candidate = 0;
                }
            }
        }
    }
    return candidate;
}

int main()
{
    int move, row, col;
    board_t board;
    move_t response;
    player_t current = 'X';
    player_t player = 'O';
    int car;
    int start;
    printf("Please enter 5 or 7 to choose your character! 5 for B; 7 for R ");
    scanf("%d", &car);
    if (car == 5)
    {
        player = 'B';
    }
    else
    {
        player = 'R';
    };
    current = player;
    init_board(board);
    printf("Please enter 1 or 2 to start first or second respectively ");
    scanf("%d",&start);
    if (start == 1){
        current = player;
    }else{
        current = other_player(player);
    };
    int placed = 0;
    while (1)
    {
        if (current == player)
        {
            print_board(board);
            printf("\n");
            print_keys(board);
            printf("Enter your move: ");
            scanf("%d", &move);
            place_XO place_object;
            place_object.row = ROW - 1;
            place_object.col = move - 1;
            placed = place_move(board, current, place_object);
            if (placed == -1){
                printf("Invalid move please enter a valid move\n");
                goto skip;
            }
        }
        else
        {
            response = best_move(board, current, 0);
            place_XO place_object;
            place_object.row = response.row;
            place_object.col = response.col;
            place_move(board, current, place_object);
        }
        if (has_won(board, current))
        {
            print_board(board);
            printf("Player %c has won!\n", current);
            break;
        }
        else if (is_full(board))
        {
            print_board(board);
            printf("Draw.\n");
            break;
        }
        current = other_player(current);
        skip:
    }

    return 0;
}
