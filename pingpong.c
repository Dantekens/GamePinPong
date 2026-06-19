#include <stdio.h>

//макросы хранащие  размер поля
#define WIDTH 80
#define HEIGHT 25
//количество очков для победы
#define WIN_POINTS 21
//размер ракеток
#define SIZE_PADDLE 3


//методы которые надо сделать реализауию (Прототипы)
int rendering(int bx, int by, int lp, int rp, int p1, int p2);
int move_paddle(int lp, char button, char up, char down);
int get_next_bx(int bx, int dx);
int get_next_by(int by, int dy);
int get_next_dx(int bx, int by, int dx, int lp, int rp);
int get_next_dy(int by, int dy);




int main(void)
{       // координаты мяча
    int bx = 40, by = 12, 
     //отскок мяча
    dx = 1 , dy = 1 ,
    //координаты ракеток
    lp = 11 , rp = 11,
    //счет
    p1 = 0 ,p2 = 0,
    //типо булево что игра идет
    game = 1;


    while(game == 1)
    {
        char button = ' ';
        rendering(bx,by,lp,rp,p1,p2);

        int is_input = 0;
        while (is_input == 0)
        {
            if(scanf(" %c", &button) == 1)
            {
                if(button == 'A' || button == 'a' || button == 'Z' 
                    || button == 'z' ||button == 'K' ||button == 'k'
                     ||button == 'M' ||button == 'm' || button == ' ')
                    is_input = 1;
                else
                    printf("ОШИБКА  Используйте только: a/z (левая), k/m (правая), Пробел (пропуск хода)");

            }
           
        }

        //тут если что подсчитываем наши значения координаты мяча ракеток  и тд
        lp = move_paddle(lp,button,'a','z');
        rp = move_paddle(rp,button,'k','m');
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