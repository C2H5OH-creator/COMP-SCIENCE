#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define F7 65
#define F8 66
#define ESC 27

void main() {
    int x = 15, y = 6, direction = 0;
    window(25, 10, 55, 20);
    textbackground(GREEN);
    clrscr();
    gotoxy(x, y);
    cprintf("$");

    while (direction != ESC) {
        if (kbhit()) {
            direction = getch();
            if (direction == 0) {
                direction = getch();
            }
            gotoxy(x, y);
            cprintf(" ");
            if (direction == F7) {
                x -= 1;
                if (x < 1) x = 31;
            }
            if (direction == F8) {
                x += 1;
                if (x > 31) x = 1;
            }
            gotoxy(x, y);
            cprintf("$");
        }
    }
}
