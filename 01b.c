#include <stdio.h>

int changes[2000] = {0};
int N = 0;

#define NMAX 4000000
int seen[NMAX] = {0};

int main() {
	while (scanf("%d",&changes[N])>0) N++;

	int i = 0;
	int change = 0;
	int cur = 0;
	int seen_i = 0;
	while (1) {
		change = changes[i++ % N];
		cur += change;
		printf("change: %5d, current frequency: %5d\n", change, cur);

		seen_i = cur + NMAX/2;    // remap -X..X to 0..2X
		if (seen[seen_i]) {
			printf("Seen %d after %d steps\n", cur, i);
			return 0;
		}
		seen[seen_i] = 1;
	}
}
