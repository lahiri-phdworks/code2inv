#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ssum.h>

#define aflcrash(cond) \
    if (!cond)         \
        assert(0);

// Guide AFL to proper values
// exit(0) is not a crash
#define assume(cond) \
    if (!cond)       \
        exit(0);

#define INV(sum, n, i, y, i2) PHI

// TODO : Automate generation of this snippet
void loopcheck(long long int sum, int n, int i, int y, int i2)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
    aflcrash(INV(sum, n, i, y, i2));
}

// TODO : Automate generation of this snippet
void postcheck(long long int sum, int n, int i, int y, int i2)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
    aflcrash(INV(sum, n, i, y, i2));
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
    long long int sum;
    long long int i2;
    int n;
    int i;
    int y;

    freopen("loopmodels.txt", "w", stderr);

    // pre-conditions
    (sum = 0LL);
    (i2 = 0LL);
    (i = 1LL);

    scanf("%d", &n);
    assume((n >= 0 && n <= 10000));

    // loop body
    assume(INV(sum, n, i, y, i2));
    assume((i <= n));
    i2 = i * i;
    (y = (i * (i + 1) * (2 * i + 1) / 6));
    sum += i2;
    loopcheck(sum, n, i, y, i2);
}