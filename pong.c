#include <stdio.h>
int move_r1(char key, int y1, int y2, int min_y, int max_y);
int mv_r2(char key, int y1, int y2, int min_y, int max_y);
void drawing_a_field(int columns, int rows, int flag) {
    int score_player1 = 20;
    int score_player2 = 20;

    int max_y = 25;
    int min_y = 1;

    int dy = 1;
    int dx = -1;

    int x_ball = 40;
    int y_ball = 12;

    int x_rocket_1 = 1;
    int y_rocket_1_start = 11;
    int y_rocket_1_end = 13;

    int x_rocket_2 = 79;
    int y_rocket_2_start = 15;
    int y_rocket_2_end = 17;

    char rocket = '%';
    char ball = '*';
    char bortik_horizon = '~';
    char space = ' ';
    char bortik_vertical = '|';
    while (flag) {
        printf("\033[0d\033[2J");

        for (int y = 0; y <= rows + 1; y++) {
            for (int x = 0; x <= columns + 1; x++) {
                if ((y == 0 && x == 0) || (y == rows + 1 && x == 0) || (y == 0 && x == columns + 1) ||
                    (y == rows + 1 && x == columns + 1)) {
                    printf("%c", '.');
                } else if (x > 0 && x < columns + 1 && (y == 0 || y == rows + 1)) {
                    printf("%c", bortik_horizon);
                }

                else if (x == x_ball && y == y_ball) {
                    printf("%c", ball);
                } else if ((x == x_rocket_1 && (y >= y_rocket_1_start && y <= y_rocket_1_end))) {
                    printf("%c", rocket);
                } else if ((x == x_rocket_2 && (y >= y_rocket_2_start && y <= y_rocket_2_end))) {
                    printf("%c", rocket);
                } else if (y != 0 && y != rows + 1 && (x == 0 || x == columns + 1)) {
                    printf("%c", bortik_vertical);
                } else {
                    printf("%c", space);
                }
            }
            printf("\n");
        }

        printf("player1 - %d:\n", score_player1);
        printf("player2 - %d:\n", score_player2);

        char key = getchar();
        if (move_r1(key, y_rocket_1_start, y_rocket_1_end, min_y, max_y) == 1) {
            y_rocket_1_start++;
            y_rocket_1_end++;

        } else if (move_r1(key, y_rocket_1_start, y_rocket_1_end, min_y, max_y) == -1) {
            y_rocket_1_start--;
            y_rocket_1_end--;
        }
        if (mv_r2(key, y_rocket_2_start, y_rocket_2_end, min_y, max_y) == 1) {
            y_rocket_2_start++;
            y_rocket_2_end++;

        } else if (mv_r2(key, y_rocket_2_start, y_rocket_2_end, min_y, max_y) == -1) {
            y_rocket_2_start--;
            y_rocket_2_end--;
        }

        if (key == ' ' || key == 'z' || key == 'a' || key == 'm' || key == 'k' || key == 'Z' || key == 'A' ||
            key == 'M' || key == 'K') {
            x_ball += dx;
            y_ball += dy;
        }

        if (x_ball == x_rocket_2 - 1 && (y_ball == y_rocket_2_end || y_ball == y_rocket_2_start ||
                                         (y_ball < y_rocket_2_end && y_ball > y_rocket_2_start))) {
            dx = -1;
        } else if (x_ball == x_rocket_2 && !(y_ball == y_rocket_2_end || y_ball == y_rocket_2_start ||
                                             (y_ball < y_rocket_2_end && y_ball > y_rocket_2_start))) {
            score_player1 += 1;
            x_ball = 40;
            y_ball = 12;
        }

        if (x_ball == x_rocket_1 + 1 && (y_ball == y_rocket_1_end || y_ball == y_rocket_1_start ||
                                         (y_ball < y_rocket_1_end && y_ball > y_rocket_1_start))) {
            dx = 1;
        } else if (x_ball == x_rocket_1 && !(y_ball == y_rocket_1_end || y_ball == y_rocket_1_start ||
                                             (y_ball < y_rocket_1_end && y_ball > y_rocket_1_start))) {
            score_player2 += 1;
            x_ball = 40;
            y_ball = 12;
        }
        if (y_ball == 25) {
            dy = -1;
        } else if (y_ball == 1) {
            dy = 1;
        }

        if (score_player1 == 21 || score_player2 == 21) {
            flag = 0;
            printf("\033[0d\033[2J");
            if (score_player1 == 21) {
                printf("WON player1\n");

            } else if (score_player2 == 21) {
                printf("WON player2\n");
            } else {
                printf("No win\n");
            }
        }
    }
}

int main() {
    int flag = 1;

    int rows = 25;
    int columns = 80;

    int score = 0;
    while (1) {
        drawing_a_field(columns, rows, flag);
        break;
        printf("Текущий ход %d - ", score);
    }

    return 0;
}

int move_r1(char key, int y1, int y2, int min_y, int max_y) {
    if ((key == 'a' || key == 'A') && y1 != min_y) {
        return -1;
    }
    if ((key == 'z' || key == 'Z') && (y2 != max_y)) {
        return 1;
    }
    return 0;
}

int mv_r2(char key, int y1, int y2, int min_y, int max_y) {
    if ((key == 'k' || key == 'K') && y1 != min_y) {
        return -1;
    }
    if ((key == 'm' || key == 'M') && (y2 != max_y)) {
        return 1;
    }
    return 0;
}
