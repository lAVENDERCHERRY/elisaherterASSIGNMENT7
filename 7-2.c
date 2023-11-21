//work cited: chatgpt, stackoverflow
#include <stdio.h>
#include <stdlib.h>

struct ColorPoint {
    long a;
    long r;
    long g;
    long b;
};

void f(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[i][j].a;
            sum += points[i][j].r;
            sum += points[i][j].g;
            sum += points[i][j].b;
        }
    }
    *dest = sum;
}

void g(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[j][i].a;
            sum += points[j][i].r;
            sum += points[j][i].g;
            sum += points[j][i].b;
        }
    }
    *dest = sum;
}




struct ColorPoint** create2DArray(int n) {
    // Array to hold a pointer to the beginning of each row
    struct ColorPoint **points = (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
    for (int i = 0; i < n; ++i) {
        // Array to hold each row
        points[i] = (struct ColorPoint *)malloc(n * sizeof(struct ColorPoint));
        for (int j = 0; j < n; ++j) {
            // Init the ColorPoint struct
            points[i][j].a = rand();
            points[i][j].r = rand();
            points[i][j].g = rand();
            points[i][j].b = rand();
        }
    }
    return points;
}

void free2DArray(struct ColorPoint** points, int n) {
    for (int i = 0; i < n; ++i) {
        free(points[i]);
    }
    free(points);
}