#include <stdio.h>

int map[2000][2000] = {0};

int main() {
	int x,y,w,h;
	int id;

	// a sweep alg would be more efficient for large X/Y/W/H, but the input is pretty small, so ain't nobody got time for that...
	while (scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) > 0) {
//		printf("%d %d %d %d", x, y, w, h);
		for (int i=x; i<x+w; i++)
			for (int j=y; j<y+h; j++)
				map[i][j]++;
	}

	int sq = 0;
	for (int i=0; i<2000; i++)
		for (int j=0; j<2000; j++)
			if (map[i][j] > 1) sq++;

	printf("%d\n", sq);

	return 0;
}
