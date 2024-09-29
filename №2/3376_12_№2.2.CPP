#include <conio.h>
#include <dos.h>

enum ScrollDirection { ENTIRE = 0, UP = 1, DOWN = 2 };

void scroll (int direction, char l_row, char l_col, char r_row, char r_col, char attr, int lines)
      {
	union REGS r;
		 if (direction == DOWN) {
		 r.h.ah = 7;
		 }
		else r.h.ah = 6;

		r.h.al = lines;
		r.h.ch =  l_row;
		r.h.cl= l_col;
		r.h.dh = r_row;
		r.h.dl= r_col;
		r.h.bh=attr;
		int86(0x10,&r,&r);
}

int main() {
    window(25, 10, 55, 20);
    clrscr();
    for (int i = 0; i < 16*16 ;i++) {
		int text = i % 16;
		int background = 15 - ((i / 16) % 16);

		textcolor(text);
		textbackground(background);
		int scrollBack = 16 * background + text;
		scroll(DOWN, 9, 24, 19, 54, scrollBack, 3);
		cprintf("Text:%d Background:%d\r", text, background);
		delay(200);
    }
    return 0;
}
