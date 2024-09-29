#include <conio.h>
#include <dos.h>
#include <bios.h>

int main() {
    window(25, 10, 55, 20);
	
    for (int i = 0; i < 16*16; i++) {
		textcolor(i % 16);
		if (i % 16 == 0) textbackground(15 - ((i / 16) % 16));
		cprintf("Text:%d Background:%d\n\n\n\r", i % 16,15 - ((i / 16) % 16));
		delay(200);
    }

    return 0;
}
