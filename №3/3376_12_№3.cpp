#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265
#define SCALE_X 22
#define SCALE_Y 50


double func(double x) {
    return pow(sin(x), 3) - pow(cos(x), 2);
}

int main() {
    //инициализация графического режима
    int graphdriver = DETECT;
    int graphmode;
    initgraph(&graphdriver, &graphmode, "");
    int graph_error_code = graphresult();
    //проверка ошибки
    if (graph_error_code != grOk) {
	printf("Error = %s\n", grapherrormsg(graph_error_code));
	getch();
	return 255;
    }
    setviewport(0, 0, getmaxx(), getmaxy(), 1);

    double startX = PI / 2;
    double endX = 8 * PI;
    double step = PI/16;
    int x0 = 50;
    int y0 = 250;
    double maxY = -5;
    //double maxX = 0;
    char label[50];
    int coordinates[220];

    setcolor(WHITE);
    outtextxy(225, 100, "Function: (sin x)^3 - (cos x)^2");
    line(x0, y0 - 150, x0, y0 + 150);
    line(x0, y0, x0 + (int)((endX + 1) * SCALE_X), y0);
    outtextxy(x0 + 580, y0 - 10, "X");
    outtextxy(x0 - 30, y0 - 150, "Y");

    // разметка X
    int PiHalf = 1;
    for (double x = startX + PI / 2; x <= endX + PI / 2; x += PI / 2) {
    int px = x0 + (int)((x - startX) * SCALE_X);
	line(px, y0 - 5, px, y0 + 5);
    if((PiHalf % 2) == 0){
	sprintf(label, "%d",PiHalf/2);
	if(((int)(x / (PI / 2)) / 2) > 9){
	    outtextxy(px - 5, y0 + 10, label);
	}
	else{outtextxy(px - 5, y0 + 10, label);}
    }
    else{
    sprintf(label, "%d", PiHalf);
    if(PiHalf > 9){
	    outtextxy(px - 10, y0 + 10, label);
	}
	else{outtextxy(px - 5, y0 + 10, label);}
	line(px - 5, y0 + 20, px + 15, y0 + 20);
	outtextxy(px, y0 + 25, "2");
    }
    outtextxy(px + 5, y0 + 10, "pi");
    PiHalf++;
    }

    // разметка Y
    for (int i = -2; i <= 2; i++) {
	int py = y0 - i * SCALE_Y;
	line(x0 - 5, py, x0 + 5, py);
	sprintf(label, "%d", i);
	outtextxy(x0 - 25, py - 5, label);
    }

    setcolor(LIGHTMAGENTA);
    x = startX;
    i = 0;
    int j = 0;
    for (x; x <= endX; x += step) {
	double y = func(x);
	if (y > maxY) {
	    maxY = y;
        //maxX = x;
	}
    int px = x0 +(int)((x) * SCALE_X);
    int py = y0 - (int)(y * SCALE_Y);
    coordinates[i++] = px;
    coordinates[i++] = py;
    }
    drawpoly(i/2,coordinates);
    sprintf(label, "Max value: y = %.2f", maxY);
    outtextxy(225, 400, label);
    rectangle(225 - 5, 400 - 5, 225 + 150 + 5, 400 + 8 + 5);

    getch();
    closegraph();
    return 0;
}
