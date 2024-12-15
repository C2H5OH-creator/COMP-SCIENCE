#include <conio.h>
#include <stdio.h>
#include <dos.h>

#define F7 65
#define F8 66
#define ESC 27


int custom_kbhit() {
    union REGS r;
    r.h.ah = 11;
    int86(0x21, &r, &r);
    return r.h.al;
}

int custom_getch() {
    union REGS r;
    r.h.ah = 7;
    int86(0x21, &r, &r);
    return r.h.al;
}

void main() {
    window(25, 10, 55, 20);
    textbackground(WHITE);
    textcolor(GREEN)
    clrscr();
    int direction = 0, x = 15, y = 6;

    gotoxy(x, y);
    cprintf("$");

    while (direction != ESC) {
        if (custom_kbhit()) {
            direction = custom_getch();
            if (direction == 0) {
                direction = custom_getch();
            }
            gotoxy(x, y);
            cprintf(" ");
            if (direction == F7) {
                x--;
                if (x < 1) x = 31;
            }
            if (direction == F8) {
                x++;
                if (x > 31) x = 1;
            }
            gotoxy(x, y);
            cprintf("$");
        }
    }
}