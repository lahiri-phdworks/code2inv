#include <130.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond) \
    if (!cond)         \
        assert(0);

#define assume(cond) \
    if (!cond)       \
        exit(0);

#define INV(d1, d2, d3, x1, x2, x3) PHI

// COMMENT : precheck template
void precheck(int d1, int d2, int d3, int x1, int x2, int x3)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
    aflcrash(INV(d1, d2, d3, x1, x2, x3));
}
// COMMENT : loopcheck template
void loopcheck(int d1, int d2, int d3, int x1, int x2, int x3)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
    aflcrash(INV(d1, d2, d3, x1, x2, x3));
}
// COMMENT : postcheck template
void post(int d1, int d2, int d3, int x1, int x2, int x3)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
    aflcrash(INV(d1, d2, d3, x1, x2, x3));
}

int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};
int unknown()
{
    int nums = sizeof(choices) / sizeof(choices[0]);
    return choices[(rand() % nums) - 1];
}

int main()
{
    // variable declarations
    int d1;
    int d2;
    int d3;
    int x1;
    int x2;
    int x3;

    scanf("%d", &x2);
    scanf("%d", &x3);
    freopen("premodels.txt", "w", stderr);

    // pre-conditions
    assume((-10000 <= x2 && x1 <= 10000));
    assume((-10000 <= x3 && x3 <= 10000));
    (d1 = 1);
    (d2 = 1);
    (d3 = 1);
    (x1 = 1);
    precheck(d1, d2, d3, x1, x2, x3);
}
