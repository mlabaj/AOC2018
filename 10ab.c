#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//#define DEBUG

typedef struct point {
    int x, y;
    int vx, vy;
} POINT;

typedef struct bbox {
    int x, y;
    int basex, basey;
} BBOX;


int iterate(POINT *p, int N, BBOX *out_box, int direction) {
    int xmin = INT_MAX;
    int ymin = INT_MAX;
    int xmax = INT_MIN;
    int ymax = INT_MIN;

    for (int i=0; i<N; i++) {
        int x = (p[i].x += p[i].vx*direction);
        int y = (p[i].y += p[i].vy*direction);

        if (x < xmin) xmin = x;
        if (x > xmax) xmax = x;
        if (y < ymin) ymin = y;
        if (y > ymax) ymax = y;
    }

    out_box->x = xmax-xmin;
    out_box->y = ymax-ymin;
    out_box->basex = xmin;
    out_box->basey = ymin;

    return direction;
}

void print(POINT *p, int N, BBOX box) {
    char **buf = malloc(box.y * sizeof(char **));
    int sizex = box.x + 1;
    int sizey = box.y + 1;

    for (int iy=0; iy<sizey; iy++)
        buf[iy] = malloc(sizex+1);

    for (int iy=0; iy<sizey; iy++) {
        for (int ix = 0; ix < sizex; ix++)
            buf[iy][ix] = ' ';
        buf[iy][sizex] = '\0';
    }

    for (int i=0; i<N; i++) {
        buf[p[i].y - box.basey][p[i].x - box.basex] = 'X';
    }

    for (int iy=0; iy<sizey; iy++) {
        printf("%s\n", buf[iy]);
    }
}

int main() {
    POINT p[400];
    int N=0;

    FILE *fp = fopen("10.in", "r");
    while (fscanf(fp, "position=< %d, %d> velocity=< %d, %d>\n", &p[N].x, &p[N].y, &p[N].vx, &p[N].vy) > 0)
        N++;
    fclose(fp);

    BBOX prev_bb = { .x = INT_MAX, .y = INT_MAX };
    BBOX bb;

    int timer = 0;

    while(1) {
        timer += iterate(p, N, &bb, +1);

        // when stars overshoot
        if (bb.x - prev_bb.x > 0) {
            // rewind last movement
            timer += iterate(p, N, &bb, -1);

            print(p, N, bb);
            printf("in %d seconds\n\n", timer);

            return 0;
        }

        prev_bb = bb;
    }
}

