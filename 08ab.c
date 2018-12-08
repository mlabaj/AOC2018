#include <stdio.h>

FILE *input;

int get_next() {
    int x;
    fscanf(input, "%d", &x);
    return x;
}

int sum_metadata() {
    int child_count = get_next();
    int metadata_count = get_next();

    int sum = 0;
    // read children recursively
    for (int i=0; i<child_count; i++)
        sum += sum_metadata();
    // read own metadata
    for (int i=0; i<metadata_count; i++)
        sum += get_next();

    return sum;
}

int root_value() {
    int child_count = get_next();
    int metadata_count = get_next();

    if (child_count > 0) {
        // read children values into array
        int child_vals[child_count];
        for (int i=0; i<child_count; i++)
            child_vals[i] = root_value();

        // sum them according to own metadata
        int val = 0;
        for (int i=0; i<metadata_count; i++) {
            int index = get_next()-1;
            if (0 <= index && index < child_count)
                val += child_vals[index];
        }

        return val;
    } else {
        // just sum own metadata
        int sum = 0;
        for (int i=0; i<metadata_count; i++)
            sum += get_next();

        return sum;
    }
}

int main() {
    input = fopen("08.in", "r");

    printf("A: %d\n", sum_metadata());

    rewind(input);

    printf("B: %d\n", root_value());

    fclose(input);
}
