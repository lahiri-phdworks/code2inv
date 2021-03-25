#include <108.h>
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

#define INV(a, c, m, j, k) PHI

// COMMENT : loopcheck template
void loopcheck(int a, int c, int m, int j, int k)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "a", a, "c", c, "m", m, "j", j, "k", k);
    aflcrash(INV(a, c, m, j, k));
}
// COMMENT : postcheck template
void post(int a, int c, int m, int j, int k)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "a", a, "c", c, "m", m, "j", j, "k", k);
    aflcrash(INV(a, c, m, j, k));
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
    int a, c, m, j, k;

    scanf("%d", &c);
    scanf("%d", &a);
    freopen("loopmodels.txt", "w", stderr);

    // pre-conditions
    assume((-10000 <= c && c <= 10000));
    assume((-10000 <= a && a <= 10000));
    assume(a <= m);
    (j = 0);
    (k = 0);

    // loopcond : (k < c)
    // loop-check program
    assume(INV(a, c, m, j, k));
    assume((k < c));
    // loop body
    {
        if (m < a)
        {
            m = a;
        }
        k = k + 1;
    }
    loopcheck(a, c, m, j, k);
}
