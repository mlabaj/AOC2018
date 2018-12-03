#include <stdio.h>

typedef struct cloth {
	int id;
	int X,Y,W,H;
} CLOTH;

CLOTH cloth[2000];
int N = 0;

int map[2000][2000] = {0};

int main() {
	int x,y,w,h;
	int id;

	while (scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) > 0) {
		cloth[N].id = id;
		cloth[N].X = x;
		cloth[N].Y = y;
		cloth[N].W = w;
		cloth[N].H = h;
		N++;
		for (int i=x; i<x+w; i++)
			for (int j=y; j<y+h; j++)
				map[i][j]++;
	}

	for (int i=0; i<N; i++) {
		CLOTH c = cloth[i];
		int theone=1;
		for (x=c.X; x<c.X+c.W; x++) {
			for (y=c.Y; y<c.Y+c.H; y++) {
				if (map[x][y]!=1) {
					theone = 0;
					break;
				}
			}
			if (!theone) break;
		}
		if (theone) {
			printf("%d\n", c.id);
			return 0;
		}
				
	}

	printf("ERROR: No cloth found.\n");

	return 1;
}
