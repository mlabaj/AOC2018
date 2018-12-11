#include <limits.h>
#include <stdio.h>
#include <assert.h>

typedef struct grid {
    int x, y;
    int power;
    int size;
} GRID;

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

int get_grid(int serial, int x, int y, int gridsize) {
    int power = 0;
    for (int ix = 0; ix<gridsize; ix++)
        for (int iy = 0; iy<gridsize; iy++)
            power += get_cell(serial, x+ix, y+iy);
    return power;
}

GRID solve(int serial, int minsize, int maxsize) {
    GRID ret;

    int maxpower = INT_MIN;
    int at_x=-1, at_y=-1, at_size=-1;

    for (int size=minsize; size<=maxsize; size++) {
        for (int ix = 1; ix <= 300 - size; ix++) {
            for (int iy = 1; iy <= 300 - size; iy++) {
                int power = get_grid(serial, ix, iy, size);
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

GRID solveA(int serial)
{
    return solve(serial, 3, 3);
}

GRID solveB(int serial)
{
    return solve(serial, 1, 300);
}

int main() {
    int serial;

    FILE *fp = fopen("11.in", "r");
    if (fscanf(fp, "%d", &serial) <= 0) return 1;
    fclose(fp);

    GRID result;

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