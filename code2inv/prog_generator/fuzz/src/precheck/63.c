#include <63.h>
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

#define INV(x, y) PHI

// COMMENT : precheck template
void precheck(int x, int y)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d\n", "x", x, "y", y);
    aflcrash(INV(x, y));
}
// COMMENT : loopcheck template
void loopcheck(int x, int y)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d\n", "x", x, "y", y);
    aflcrash(INV(x, y));
}
// COMMENT : postcheck template
void post(int x, int y)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d\n", "x", x, "y", y);
    aflcrash(INV(x, y));
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
    int x;
    int y;

    scanf("%d", &x);
    freopen("premodels.txt", "w", stderr);

    // pre-conditions
    (x = 1);
    precheck(x, y);
}
