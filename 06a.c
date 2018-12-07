#include <stdio.h>

typedef struct point {
	int x, y;
} POINT;

POINT p[1000];
int N;

int main() {
	FILE *fp;

    fp = fopen("06.in", "r");
    while (fscanf(fp, "%d, %d", &p[N].x, &p[N].y)>0) N++;
    fclose(fp);
    

    return 0;
}
