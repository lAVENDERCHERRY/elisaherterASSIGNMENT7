//work cited: chatgpt, stackoverflow
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ColorPoint {
    long a;
    long r;
    long g;
    long b;
};

void f(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;

    // Memory reads for points[0][0].a, points[0][0].r, etc.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Calculate the memory address for points[i][j].a
            long address_a = (long)&points[i][j].a;

            // Calculate the cache block address (aligned to 64B boundary)
            long block_address = address_a & ~0x3F;

            // Calculate the tag for the cache block
            long tag = block_address >> 6;

            // Check if the tag matches the current content of the cache
            // Assume cache is initially empty
            if (tag == 0) {
                // printf("Cache Hit for points[%d][%d].a\n", i, j);
            } else {
                // printf("Cache Miss for points[%d][%d].a\n", i, j);
            }

            // Similar calculations for points[i][j].r, points[i][j].g, and points[i][j].b
            // ...

            sum += points[i][j].a;
            sum += points[i][j].r;
            sum += points[i][j].g;
            sum += points[i][j].b;
        }
    }

    *dest = sum;
}

// Given n = 4, the first 8 memory reads would correspond to:

// points[0][0].a
// points[0][0].r
// points[0][0].g
// points[0][0].b
// points[0][1].a
// points[0][1].r
// points[0][1].g
// points[0][1].b

// The pattern of hits will likely continue throughout execution due to spatial locality. 
// As the loop iterates over the rows (i), the memory accesses are sequential, and the data in the same cache block is reused, resulting in cache hits.

void g(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;

    // Memory reads for points[0][0].a, points[0][0].r, etc.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Calculate the memory address for points[j][i].a
            long address_a = (long)&points[j][i].a;

            // Calculate the cache block address (aligned to 64B boundary)
            long block_address = address_a & ~0x3F;

            // Calculate the tag for the cache block
            long tag = block_address >> 6;

            // Check if the tag matches the current content of the cache
            // Assume cache is initially empty
            if (tag == 0) {
                // printf("Cache Hit for points[%d][%d].a\n", j, i);
            } else {
                // printf("Cache Miss for points[%d][%d].a\n", j, i);
            }

            // Similar calculations for points[j][i].r, points[j][i].g, and points[j][i].b
            // ...

            sum += points[j][i].a;
            sum += points[j][i].r;
            sum += points[j][i].g;
            sum += points[j][i].b;
        }
    }

    *dest = sum;
}

// Given n = 4, the first 8 memory reads would correspond to:

// points[0][0].a
// points[0][0].r
// points[0][0].g
// points[0][0].b
// points[1][0].a
// points[1][0].r
// points[1][0].g
// points[1][0].b

// The pattern of hits and misses will likely not continue throughout execution due to the non-contiguous nature of the memory accesses in columns.
// As the loop iterates over the columns (j), the memory accesses are not sequential, and the data is not in the same cache block, resulting in cache misses. 


// SUMMARY
// In summary, the primary difference between functions f and g is their memory access pattern: f uses a row-major order, and g uses a column-major order. 
// The efficiency of these patterns in terms of cache hits and misses can depend on various factors and may vary based on the specific context and hardware.

struct ColorPoint** create2DArray(int n) {
    struct ColorPoint **points = (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
    for (int i = 0; i < n; ++i) {
        points[i] = (struct ColorPoint *)malloc(n * sizeof(struct ColorPoint));
        for (int j = 0; j < n; ++j) {
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

void measureTime(struct ColorPoint** points, int n, void (*func)(struct ColorPoint**, int, long*), const char* funcName) {
    clock_t start, end;
    long dest;

    start = clock();
    func(points, n, &dest);
    end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%s time: %f seconds\n", funcName, cpu_time_used);
}

int main() {
    int n = 2048;
    struct ColorPoint **points = create2DArray(n);
    
    // Measure time for function f
    measureTime(points, n, f, "f");

    // Measure time for function g
    measureTime(points, n, g, "g");

    // Free allocated memory
    free2DArray(points, n);

    return 0;
}

//   The relative speed of f and g can be influenced by the memory access patterns and how well
//   these patterns align with the cache organization. The f function accesses memory in a
//   row-major order, while the g function accesses memory in a column-major order.
  
//   The performance may depend on the specific characteristics of the CPU cache, such as cache line size,
//   cache associativity, and the presence of optimizations performed by the compiler.
  
//   In some cases, f may exhibit better spatial locality, resulting in more cache hits,
//   while g may suffer from cache misses due to a less cache-friendly access pattern.
//   So therefore, f will be more efficent but there are factors in which can influence the run time. 
  
//   However, the actual performance can be influenced by various factors, and the results may vary
//   based on the specific hardware architecture and compiler optimizations.