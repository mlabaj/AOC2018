#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str[300];
int N = 0;

int cmp(const void* a, const void* b)
{
    return strcmp(*((char**) a), *((char**) b));
}

int main() {
	do {
		str[N] = malloc(50*sizeof(char));
	} while (scanf("%49s", str[N++])>0);
	N--;	// remove last failed read

	for (int i=0; i<N-1; i++) {
		for (int j=i+1; j<N; j++) {
			char *a = str[i];
			char *b = str[j];

			int len = strlen(a);
			if (strlen(b) != len) {
				printf("ERROR! ID lengths are different: %s and %s.\n", a, b);
				return 1;
			}

			char common[50];
			int clen = 0;
			int found = 0;
			for (int k=0; k<len; k++) {
				common[clen++] = a[k];
				if (a[k]==b[k]) continue;

				if (found != 0)
				{
					// more than one difference
					found = 0;
					break;
				}

				found = 1;
				clen--;
			}
			if (found) {
				common[clen] = '\0';
				printf("%s\n", common);
				return 0;
			}
		}
		
	}

	printf("ERORR! No such IDs found.\n");
	return 1;
}
