#include <dos.h>
#include <stdio.h>
#include <conio.h>

void interrupt (*oldInt8)();

void interrupt newInt8() {
    static unsigned int counter = 0;
    if (++counter >= 10) {
        counter = 0;
        outportb(0x43, 0xB6);
        outportb(0x42, 0x50);
        outportb(0x42, 0x02);
        outportb(0x61, inportb(0x61) | 3);
        delay(100);
        outportb(0x61, inportb(0x61) & 0xFC);
    }
    (*oldInt8)();
}

void main() {
    disable();
    oldInt8 = getvect(8);
    setvect(8, newInt8);
    enable();
    printf("PRESS ANY KEY TO EXIT.\n");
    getch();
    disable();
    setvect(8, oldInt8);
    enable();
}
