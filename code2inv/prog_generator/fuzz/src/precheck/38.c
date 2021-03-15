#include <38.h>
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

#define INV(n, c) PHI

// TODO : Automate generation of this snippet
void precheck(int n, int c)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d\n", "n", n, "c", c);
    aflcrash(INV(n, c));
}

// TODO : Automate generation of this snippet
void loopcheck(int n, int c)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d\n", "n", n, "c", c);
    aflcrash(INV(n, c));
}

// TODO : Automate generation of this snippet
void postcheck(int n, int c)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d\n", "n", n, "c", c);
    aflcrash(INV(n, c));
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
    int n;
    int c;

    freopen("premodels.txt", "w", stderr);

    scanf("%d", &n);
    scanf("%d", &c);

    // pre-conditions
    assume((-10000 <= n && n <= 10000));
    assume((-10000 <= c && c <= 10000));

    precheck(n, c);
}
