#define MAX_NAME_LEN 50
#define numRow 3
#define numCol 3
#define toWin 3
enum Bool { False, True };
enum status { P1_TURN, P2_TURN, P1_WON, P2_WON, DRAW };
typedef enum Bool boolean;
const char SPACE = '-';
char X_SYMBOL = 'X';
char O_SYMBOL = 'O';

struct game {

    char board[numRow][numCol];
    char playerNames[2][MAX_NAME_LEN];
    int status;
    boolean finished;
};

void play_game();

void getNames(char* name1, char* name2);

struct game* initialise_game(char *name1, char *name2);

char** getBlankBoard();

void draw_banner();

void display_board(char board[numRow][numCol]);

void print_status(struct game* p_game_info);

void display_board_positions();

void process_move(struct game* game_info, int* moves);

void check_finished(struct game* p_game_info, int* moves);

void set_winner(struct game* p_game_info, char SYMBOL);

int time();
