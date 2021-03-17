#include <21.h>
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

#define INV(x, m, n, z1, z2, z3) PHI

// COMMENT : precheck template
void precheck(int x, int m, int n, int z1, int z2, int z3)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n, "z1", z1, "z2", z2, "z3", z3);
    aflcrash(INV(x, m, n, z1, z2, z3));
}
// COMMENT : loopcheck template
void loopcheck(int x, int m, int n, int z1, int z2, int z3)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n, "z1", z1, "z2", z2, "z3", z3);
    aflcrash(INV(x, m, n, z1, z2, z3));
}
// COMMENT : postcheck template
void post(int x, int m, int n, int z1, int z2, int z3)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n, "z1", z1, "z2", z2, "z3", z3);
    aflcrash(INV(x, m, n, z1, z2, z3));
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
    int z1;
    int z2;
    int z3;
    int x;
    int m;
    int n;

    scanf("%d", &n);
    scanf("%d", &x);
    scanf("%d", &m);
    freopen("postmodels.txt", "w", stderr);

    // pre-conditions
    (x = 1);
    (m = 1);
    assume((-10000 <= m && m <= 10000));
    assume((-10000 <= x && x <= 10000));
    assume((-10000 <= n && n <= 10000));

    // post-check program
    assume(INV(x, m, n, z1, z2, z3));
    assume(!(x < n));

    // post-condition
    if (n > 1)
    {
        fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", x, m, n, z1, z2, z3);
        assert(m < n);
    }
}
