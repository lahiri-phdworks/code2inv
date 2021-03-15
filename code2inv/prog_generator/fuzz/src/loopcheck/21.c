#include <21.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond) \
    if (!cond)         \
        assert(0);

// Guide AFL to proper values
// exit(0) is not a crash
#define assume(cond) \
    if (!cond)       \
        exit(0);

#define INV(x, m, n) PHI

// TODO : Automate generation of this snippet
void precheck(int x, int m, int n)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n);
    aflcrash(INV(x, m, n));
}

// TODO : Automate generation of this snippet
void loopcheck(int x, int m, int n)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n);
    aflcrash(INV(x, m, n));
}

// TODO : Automate generation of this snippet
void postcheck(int x, int m, int n)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n);
    aflcrash(INV(x, m, n));
}

int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};
int unknown()
{
    int nums = sizeof(choices) / sizeof(choices[0]);
    return choices[(rand() % nums) - 1];
}

int main()
{
    int x;
    int m;
    int n;
    freopen("loopmodels.txt", "w", stderr);

    (x = 1);
    (m = 1);
    scanf("%d", &n);

    assume(INV(x, m, n));
    assume((x < n));
    if (unknown())
    {
        m = x;
    }
    x = x + 1;
    loopcheck(x, m, n);
}
