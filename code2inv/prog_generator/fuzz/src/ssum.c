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

#define INV(sum, n, i, y) PHI

// TODO : Automate generation of this snippet
void precheck(long long int sum, int n, int i, int y, int i2)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
    aflcrash(INV(sum, n, i, y));
}

// TODO : Automate generation of this snippet
void loopcheck(long long int sum, int n, int i, int y, int i2)
{
    char buffer[30];
    fprintf(stderr, "Loop : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
    aflcrash(INV(sum, n, i, y));
}

// TODO : Automate generation of this snippet
void postcheck(long long int sum, int n, int i, int y, int i2)
{
    char buffer[30];
    fprintf(stderr, "Post : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
    aflcrash(INV(sum, n, i, y));
}

int main()
{

    // variable declarations
    long long int sum;
    long long int i2;
    int n;
    int i;
    int y;

    freopen("models.txt", "w", stderr);

    // pre-conditions
    (sum = 0LL);
    (i2 = 0LL);
    (i = 1LL);

    assume((n > 0 && n < 100000))

        precheck(sum, n, i, y, i2);

    // loop body
    for (; i <= n; i++)
    {
        i2 = i * i;
        (y = (i * (i + 1) * (2 * i + 1) / 6));

        // assert(sum == y);
        loopcheck(sum, n, i, y, i2);
        sum += i2;
    }

    // Post Conditions
    postcheck(sum, n, i, y, i2);
    assert((sum == ((n * (n + 1) * (2 * n + 1)) / 6)));
    return 0;
}