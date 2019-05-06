#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

void play_game() {

    char name1[MAX_NAME_LEN];
    char name2[MAX_NAME_LEN];
    int moves = 0;

    getNames(name1, name2);
    struct game* p_game_info = initialise_game(name1, name2);

    while(!p_game_info->finished) {

        system("cls");

        printf("Xs and Os!\n");
        draw_banner();
        display_board(p_game_info->board);
        display_board_positions();
        print_status(p_game_info);
        process_move(p_game_info, &moves);
        check_finished(p_game_info, &moves);
    }

     system("cls");
     printf("Xs and Os!\n");
     draw_banner();
     display_board(p_game_info->board);
     print_status(p_game_info);
}

void getNames(char* name1, char* name2) {

    printf("Enter first players name: ");

    int i;
	boolean finish = False;

	for (i = 0; finish == False && i < MAX_NAME_LEN; ++i) {

        name1[i] = getchar();

		if (name1[i] == '\n') {

            name1[i] = '\0';
			finish = True;
		}
	}

	printf("Enter second players name: ");

    finish = False;

	for (i = 0; finish == False && i < MAX_NAME_LEN; ++i) {

        name2[i] = getchar();

		if (name2[i] == '\n') {

            name2[i] = '\0';
			finish = True;
		}
	}
}

struct game* initialise_game(char name1[MAX_NAME_LEN], char name2[MAX_NAME_LEN]) {

    struct game* p_game_info = malloc(sizeof(struct game));
    srand(time(0));

    int x, y;

    for(x = 0; x < numRow; ++x)
        for(y = 0; y < numCol; ++y)
            p_game_info->board[x][y] = SPACE;

    if(rand()%2 == 1)
        p_game_info->status = P1_TURN;

    else
        p_game_info->status = P2_TURN;

    if(rand()%2 == 1) {

        X_SYMBOL = 'O';
        O_SYMBOL = 'X';
    }

    strncpy(p_game_info->playerNames[0], name1, MAX_NAME_LEN);
    strncpy(p_game_info->playerNames[1], name2, MAX_NAME_LEN);

    p_game_info->finished = False;

    return p_game_info;
}

void draw_banner() {

    printf("\n-----------\n");
    printf("GAME STATUS\n");
    printf("-----------\n");
}

void display_board(char board[numRow][numCol]) {

    printf("\nGame State:\n");
    int x, y;

    for(x = 0; x < numRow; ++x) {

        printf("\t");

        for(y = 0; y < numCol; ++y) {

            if(y != numCol-1)
                printf(" %c |", board[x][y]);

            else
                printf(" %c ", board[x][y]);
        }

        printf("\n\t");

        for(y = 0; y < numCol; ++y) {

            if(x != numRow - 1) {

                if(y != numCol - 1)
                    printf("---|");

                else
                    printf("---\n");
            }
        }
    }

     printf("\n");
}

void print_status(struct game* p_game_info) {

    if(p_game_info->status == P1_TURN)
        printf("\nPlayer 1s turn -> %s's Turn: ", p_game_info->playerNames[0]);

    else if(p_game_info->status == P2_TURN)
        printf("\nPlayer 2s turn -> %s's Turn: ", p_game_info->playerNames[1]);

    else if(p_game_info->status == P1_WON)
        printf("\nPlayer 1 won -> Well done %s you have won.\n", p_game_info->playerNames[0]);

    else if(p_game_info->status == P2_WON)
        printf("\nPlayer 2 won -> Well done %s you have won.\n", p_game_info->playerNames[1]);

    else if(p_game_info->status == DRAW)
        printf("\nIt's a Draw -> Game Over.\n");
}

void display_board_positions() {

    int maxNum = (numRow * numCol) - 1;
    int spaces = 1, z;

    for(z = 1; z <= maxNum; z *= 10)
        spaces ++;

    printf("\n\nPick Your Position:\n");
    int x, y, count = 0;

    for(x = 0; x < numRow; ++x) {

        printf("\t");

        for(y = 0; y < numCol; ++y) {

            for(z = 1; z < spaces; ++z)
                if(count >= 10^z)
                    printf(" ");

            if(y != numCol - 1)
                printf("%d|", count);

            else
                printf("%d", count);

            ++count;
        }

        printf("\n\t");

        for(y = 0; y < numCol; ++y) {

            if(x != numRow - 1) {

                for(z = 1; z <= spaces; ++z)
                    printf("-");

                if(y != numCol - 1)
                    printf("|");

                else
                    printf("\n");
            }
        }
    }

     printf("\n");
}

void get_row_col(int position, int* row, int* col) {

    *row = position/numCol;
    *col = position%numCol;
}

void  process_move(struct game* p_game_info, int* moves) {

    char dummy_char = getchar();
    int position = - 1;
	boolean finish = False;
	int multiplier = 1;

	while (finish == False) {
		if (dummy_char == '\n')
			finish = True;
		else {

            if(position == -1)
                position = 0;

            position *= multiplier;
			position += (dummy_char-48);
			dummy_char = getchar();
			multiplier *= 10;
		}
	}

	int row, col;
	get_row_col(position, &row, &col);

    if(p_game_info->status == P1_TURN && p_game_info->board[row][col] == SPACE) {

        p_game_info->board[row][col] = X_SYMBOL;
        p_game_info->status = P2_TURN;
        ++*moves;
    }

    else if(p_game_info->status == P2_TURN && p_game_info->board[row][col] == SPACE) {

        p_game_info->board[row][col] = O_SYMBOL;
        p_game_info->status = P1_TURN;
        ++*moves;
    }
}

void check_finished(struct game* p_game_info, int* moves) {

    // Divide each row into boxes of however many is required to win
    // Example:  6x6 with 3 to win. We check the 3x3 of rows 1, 2 & 3 and column 1, 2 & 3 for a winner
    //           Next we check the 3x3 of rows 1, 2 & 3 and column 2, 3 & 4 for winner.
    //           Iterate through all possible 3x3s that can be made with rows 1, 2 & 3 then repeat for rows 2, 3 & 4.
    //           We do this until we have checked every possible 3x3. If it was 4 required to win we would divide the board
    //           into all possible 4x4s and check for winners.

    // Calculate how many checks we need to do
    int rowCheck = numRow - toWin + 1;
    int colCheck = numCol - toWin + 1;
    int i, x, y, a, b;
    char SYMBOL = X_SYMBOL;
    boolean winner = False;

    // 2 Players
    for(i = 0; i < 2; ++i) {

        // Check rows
        for(a = 0; a < rowCheck; ++a) {

            // Check columns
            for(b = 0; b < colCheck; ++b) {

                // From here we're just checking all possible combinations in a box of length and height being however many is required to win.
                // We check if each row has all the same symbols (rows are x), and we check if each column has all the same symbols (columns are y)
                // Then we check the 2 possible diagonals and we're done.

                // Check rows
                for(x = 0; x < toWin; ++x) {

                    winner = True;

                    for(y = 0; y < toWin; ++y)
                        if(p_game_info->board[x + a][y + b] != SYMBOL)
                            winner = False;

                    if(winner)
                        set_winner(p_game_info, SYMBOL);
                }

                // Check columns
                for(y = 0; y < toWin; ++y) {

                    winner = True;

                    for(x = 0; x < toWin; ++x)
                        if(p_game_info->board[x + a][y + b] != SYMBOL)
                            winner = False;

                    if(winner)
                        set_winner(p_game_info, SYMBOL);
                }

                winner = True;

                // Check diagonal
                for(x = 0; x < toWin; ++x)
                    if(p_game_info->board[x + a][x + b] != SYMBOL)
                            winner = False;

                if(winner)
                    set_winner(p_game_info, SYMBOL);

                winner = True;

                // Check other diagonal
                for(x = 0; x < toWin; ++x)
                    if(p_game_info->board[x + a][(toWin - x - 1) + b] != SYMBOL)
                            winner = False;

                if(winner)
                    set_winner(p_game_info, SYMBOL);
            }
        }
        SYMBOL = O_SYMBOL;
    }

    if(!p_game_info->finished && *moves == (numRow * numCol)) {

        p_game_info->status = DRAW;
        p_game_info->finished = True;
    }
}

void set_winner(struct game* p_game_info, char SYMBOL) {

    if(SYMBOL == X_SYMBOL)
        p_game_info->status = P1_WON;

    else
        p_game_info->status = P2_WON;

    p_game_info->finished = True;
}
