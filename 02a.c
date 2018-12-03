#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[50];
int twos = 0;
int threes = 0;
int hist[27];

int main() {
	while (scanf("%49s", str)>0) {
		int len = strlen(str);

		memset(hist, 0, 27*sizeof(int));

		for (int i=0; i<len; i++) {
			char c = str[i];
			if (c > 'z' || c < 'a') {
				printf("Unknown character: %c\n", c);
				return 1;
			}
			hist[c-'a']++;
		}

		int two=0;
		int three=0;
		for (int i=0; i<26; i++) {
			if (hist[i] == 2) {
				two = 1;
				if (three) break;
			}
			if (hist[i] == 3) {
				three = 1;
				if (two) break;
			}
		}

		twos += two;
		threes += three;
	}

	printf("%d\n", twos*threes);

	return 0;
}
