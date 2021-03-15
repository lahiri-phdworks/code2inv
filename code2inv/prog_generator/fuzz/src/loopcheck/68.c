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
    int n;
    int y;
    int x;

    freopen("loopmodels.txt", "w", stderr);

    // pre-conditions
    (x = 1);
    scanf("%d", &n);
    assume((-10000 <= n && n <= 10000));

    assume(INV(n, y, x));
    assume((x <= n));
    y = n - x;
    x = x + 1;
    loopcheck(n, y, x);
}
