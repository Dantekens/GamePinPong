#include <stdio.h>

// макросы хранащие  размер поля
#define WIDTH 80
#define HEIGHT 25
// количество очков для победы
#define WIN_POINTS 21
// размер ракеток
#define SIZE_PADDLE 3

// методы которые надо сделать реализауию (Прототипы)
int rendering(int bx, int by, int lp, int rp, int p1, int p2);
int move_paddle(int paddle, char button, int side);
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

int main(void) {  // координаты мяча
    int bx = 40, by = 12,
        // отскок мяча
        dx = 1, dy = 1,
        // координаты ракеток
        lp = 11, rp = 11,
        // счет
        p1 = 0, p2 = 0, 
        // типо булево что игра идет
        game = 1;

    while (game == 1) {
        char button = ' ';
        rendering(bx, by, lp, rp, p1, p2);

        int is_input = 0;
        while (is_input == 0) {
            char clear;
            if (scanf("%c", &button )== 1) {
               
                 if(button == '\n') continue;

                if (button == 'A' || button == 'a' || button == 'Z' || button == 'z' || button == 'K' ||
                    button == 'k' || button == 'M' || button == 'm' || button == ' ')
                    is_input = 1;
                else
                    printf("ОШИБКА  Используйте только: a/z (левая), k/m (правая), Пробел (пропуск хода)");
            }
        }

        // тут если что подсчитываем наши значения координаты мяча ракеток  и тд
        lp = move_paddle(lp, button, 0);
        rp = move_paddle(rp, button, 1);
        dx = get_next_dx(bx, by, dx, lp, rp);
        dy = get_next_dy(by, dy);
        bx = get_next_bx(bx, dx);
        by = get_next_by(by, dy);

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

        if (p1 >= WIN_POINTS || p2 >= WIN_POINTS) {
            game = 0;
        }
        if (p1 >= WIN_POINTS) printf("Игрок 1 победил!\n");
        if (p2 >= WIN_POINTS) printf("Игрок 2 победил!\n");
    }
    return 0;
}

int move_paddle(int paddle, char button, int side) {
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
    printf("\e[1;1H\e[2J");
    printf("Управлкение: a/z (левая), k/m (правая), Пробел (пропуск хода)\n");
    printf("\t\t\t\tсчет: %d | %d\n", p1, p2);

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1)
                printf("-");
            else if (j == 0 || j == WIDTH - 1)
                printf("|");
            else if (i == by && j == bx)
                printf("O");
            else if (j == 2 && i >= lp && i <= lp + 2)
                printf("|");
            else if (j == WIDTH - 3 && i >= rp && i <= rp + 2)
                printf("|");

            else
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}
