#include <ncurses.h>

// макросы хранащие размер поля
#define WIDTH 80
#define HEIGHT 25
// количество очков для победы
#define WIN_POINTS 21
// размер ракеток
#define SIZE_PADDLE 3
// задержка кадра в миллисекундах (скорость отрисовки/опроса клавиатуры)
#define FRAME_DELAY_MS 10
// сколько кадров проходит между шагами мяча (скорость мяча)
#define BALL_STEP_FRAMES 20

// Прототипы
int rendering(int bx, int by, int lp, int rp, int p1, int p2);
int move_paddle(int paddle, int button, int side);
int get_next_bx(int bx, int dx) { return bx + dx; }
int get_next_by(int by, int dy) { return by + dy; }

int get_next_dx(int bx, int by, int dx, int lp, int rp) {
    int target_dx = dx;
    if (bx == 2 && by >= lp && by <= (lp + SIZE_PADDLE - 1)) target_dx = 1;
    if (bx == WIDTH - 3 && by >= rp && by <= (rp + SIZE_PADDLE - 1)) target_dx = -1;
    return target_dx;
}

int get_next_dy(int by, int dy) {
    int target_dy = dy;
    if (by <= 1 || by >= HEIGHT - 2) target_dy = -target_dy;
    return target_dy;
}

int main(void) {
    // координаты мяча
    int bx = 40, by = 12,
        // отскок мяча
        dx = 1, dy = 1,
        // координаты ракеток
        lp = 11, rp = 11,
        // счет
        p1 = 0, p2 = 0,
        // типо булево что игра идет
        game = 1,
        // счетчик кадров для управления скоростью мяча
        frame_counter = 0;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while (game == 1) {
        int button = getch();

        // обработка перемещения весел каждый кадр (реальное время)
        lp = move_paddle(lp, button, 0);
        rp = move_paddle(rp, button, 1);

        // мяч двигается раз в BALL_STEP_FRAMES кадров,
        // чтобы скорость мяча не зависела от частоты опроса клавиатуры
        if (frame_counter >= BALL_STEP_FRAMES) {
            dx = get_next_dx(bx, by, dx, lp, rp);
            dy = get_next_dy(by, dy);
            bx = get_next_bx(bx, dx);
            by = get_next_by(by, dy);
            frame_counter = 0;
        } else {
            ++frame_counter;
        }

        if (bx <= 0) {
            p2++;
            bx = 40;
            by = 12;
            dx = 1;
            dy = 1;
        }
        if (bx >= WIDTH - 1) {
            p1++;
            bx = 40;
            by = 12;
            dx = -1;
            dy = 1;
        }

        rendering(bx, by, lp, rp, p1, p2);

        if (p1 >= WIN_POINTS || p2 >= WIN_POINTS) {
            game = 0;
        }

        napms(FRAME_DELAY_MS);
    }

    nodelay(stdscr, FALSE);
    move(HEIGHT + 3, 0);
    if (p1 >= WIN_POINTS) printw("Player 1 wins! Press any key to exit..\n");
    if (p2 >= WIN_POINTS) printw("Player 2 wins! Press any key to exit..\n");
    refresh();
    getch();

    endwin();
    return 0;
}

int move_paddle(int paddle, int button, int side) {
    int res = paddle;
    if (side == 0) {
        if ((button == 'a' || button == 'A') && paddle > 1)
            --res;
        else if ((button == 'z' || button == 'Z') && paddle < HEIGHT - 4)
            ++res;
    } else if (side == 1) {
        if ((button == 'k' || button == 'K') && paddle > 1)
            --res;
        else if ((button == 'm' || button == 'M') && paddle < HEIGHT - 4)
            ++res;
    }

    return res;
}

int rendering(int bx, int by, int lp, int rp, int p1, int p2) {
    clear();
    printw("Controls: a/z (left), k/m (right), Space (skip turn)\n");
    printw("\t\t\t\tcheck: %d | %d\n", p1, p2);

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1)
                printw("-");
            else if (j == 0 || j == WIDTH - 1)
                printw("|");
            else if (i == by && j == bx)
                printw("O");
            else if (j == 2 && i >= lp && i <= lp + 2)
                printw("|");
            else if (j == WIDTH - 3 && i >= rp && i <= rp + 2)
                printw("|");
            else
                printw(" ");
        }
        printw("\n");
    }

    refresh();
    return 0;
}
