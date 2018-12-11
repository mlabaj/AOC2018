#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct square {
    int x, y;
    int power;
    int size;
} SQUARE;

int get_cell(int serial, int x, int y) {
    // Find the fuel cell's rack ID, which is its X coordinate plus 10.
    int id = x+10;
    // Begin with a power level of the rack ID times the Y coordinate.
    int power = id*y;
    // Increase the power level by the value of the grid serial number (your puzzle input).
    power += serial;
    // Set the power level to itself multiplied by the rack ID.
    power *= id;
    // Keep only the hundreds digit of the power level (so 12345 becomes 3; numbers with no hundreds digit become 0).
    power = (power / 100) % 10;
    // Subtract 5 from the power level.
    power -= 5;

    return power;
}

// SUMS[x][y] = sum of cells from x, y to lower right corner of the grid
//   includes last row/column (x = 301 or y = 301) as boundaries
int SUMS[302][302];

void prepare(int serial) {
    memset(SUMS, 0, sizeof(SUMS));

    for (int iy=300; iy>=0; iy--) {
        int rowsum = 0;
        for (int ix=300; ix>=0; ix--) {
            rowsum += get_cell(serial, ix, iy);
            SUMS[ix][iy] = SUMS[ix][iy+1] + rowsum;
        }
    }
}

int get_square(int x, int y, int size) {
    // - (+) get sum from point x,y to the end of the grid
    // - (-) remove everything to the right of the square
    // - (-) remove everything under the square
    // - area to the-right-and-below (from lower right corner of the square) was added once and removed twice,
    //   add it back once more, to cancel it out
    return SUMS[x][y] - SUMS[x+size][y] - SUMS[x][y+size] + SUMS[x+size][y+size];
}

SQUARE solve(int serial, int minsize, int maxsize) {
    SQUARE ret;

    int maxpower = INT_MIN;
    int at_x=-1, at_y=-1, at_size=-1;

    prepare(serial);
    for (int size=minsize; size<=maxsize; size++) {
        for (int ix = 1; ix <= 300 - size; ix++) {
            for (int iy = 1; iy <= 300 - size; iy++) {
                int power = get_square(ix, iy, size);
                if (power > maxpower)
                    maxpower = power, at_x = ix, at_y = iy, at_size = size;
            }
        }
    }
    ret.power = maxpower;
    ret.x = at_x;
    ret.y = at_y;
    ret.size = at_size;

    return ret;
}

SQUARE solveA(int serial)
{
    return solve(serial, 3, 3);
}

SQUARE solveB(int serial)
{
    return solve(serial, 1, 300);
}

int main() {
    int serial;

    FILE *fp = fopen("11.in", "r");
    if (fscanf(fp, "%d", &serial) <= 0) return 1;
    fclose(fp);

    SQUARE result;

    result = solveA(18);
    assert(result.x == 33);
    assert(result.y == 45);
    assert(result.power == 29);

    result = solveA(42);
    assert(result.x == 21);
    assert(result.y == 61);
    assert(result.power == 30);

    result = solveA(serial);
    printf("A: Achieved max power %d at %d,%d\n", result.power, result.x, result.y);

    result = solveB(18);
    assert(result.x == 90);
    assert(result.y == 269);
    assert(result.power == 113);
    assert(result.size == 16);

    result = solveB(42);
    assert(result.x == 232);
    assert(result.y == 251);
    assert(result.power == 119);
    assert(result.size == 12);

    result = solveB(serial);
    printf("B: Achieved max power %d at %d,%d,%d\n", result.power, result.x, result.y, result.size);

    return 0;
}