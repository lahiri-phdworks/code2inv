#include <68.h>
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

#define INV(n, y, x) PHI

// TODO : Automate generation of this snippet
void precheck(int n, int y, int x)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n", "n", n, "y", y, "x", x);
    aflcrash(INV(n, y, x));
}

// TODO : Automate generation of this snippet
void loopcheck(int n, int y, int x)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n", "n", n, "y", y, "x", x);
    aflcrash(INV(n, y, x));
}

// TODO : Automate generation of this snippet
void postcheck(int n, int y, int x)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n", "n", n, "y", y, "x", x);
    aflcrash(INV(n, y, x));
}

int main()
{
    // variable declarations
    int n;
    int y;
    int x;

    freopen("premodels.txt", "w", stderr);

    // pre-conditions
    scanf("%d", &n);

    (x = 1);

    assume((x == 1));
    assume((-10000 <= n && n <= 10000));
    precheck(n, y, x);
}
