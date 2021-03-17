#include <106.h>
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

#define INV(a, m, j, k) PHI

// COMMENT : precheck template
void precheck(int a, int m, int j, int k)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "a", a, "m", m, "j", j, "k", k);
    aflcrash(INV(a, m, j, k));
}
// COMMENT : loopcheck template
void loopcheck(int a, int m, int j, int k)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n", "a", a, "m", m, "j", j, "k", k);
    aflcrash(INV(a, m, j, k));
}
// COMMENT : postcheck template
void post(int a, int m, int j, int k)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", "a", a, "m", m, "j", j, "k", k);
    aflcrash(INV(a, m, j, k));
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
    int a, m, j, k;

    scanf("%d", &m);
    scanf("%d", &a);
    freopen("postmodels.txt", "w", stderr);

    // pre-conditions
    assume((-10000 <= m && m <= 10000));
    assume((-10000 <= a && a <= 10000));
    assume(a <= m);
    assume(j < 1);
    (k = 0);

    // post-check program
    assume(INV(a, m, j, k));
    assume(!(k < 1));
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", a, m, j, k);
    // post-condition
    assert(a >= m);
}
