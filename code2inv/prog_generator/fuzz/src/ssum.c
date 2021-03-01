#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ssum.h>

#define fail(cond) \
    if (!cond)     \
        assert(0);

#define exitpass(cond) \
    if (!cond)         \
        exit(-1);

#define INV(sum, n, i, y) PHI

void check(int sum, int n, int i, int y, int i2)
{
    char buffer[30];
    fprintf(stderr, "%s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
    fail(INV(sum, n, i, y));
}

int main()
{

    // variable declarations
    long long int sum;
    int n;
    int i;
    int y;
    int i2;
    freopen("models.txt", "w", stderr);
    fprintf(stderr, "\nModel : \n");

    // pre-conditions
    (sum = 0LL);
    (i2 = 0LL);
    (i = 1LL);

    scanf("%d", &n);

    // restrict value of "n"
    exitpass((n > 0 && n < 6000))

        check(sum, n, i, y, i2);

    // loop body
    for (; i <= n; i++)
    {
        i2 = i * i;
        (y = (i * (i + 1) * (2 * i + 1) / 6));

        // assert(sum == y);
        check(sum, n, i, y, i2);
        sum += i2;
    }

    // Post Conditions
    check(sum, n, i, y, i2);
    assert((sum == ((n * (n + 1) * (2 * n + 1)) / 6)));
    return 0;
}