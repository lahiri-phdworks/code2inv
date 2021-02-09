#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

    // variable declarations
    int sum;
    int n;
    int i;
    int y;

    // pre-conditions
    (sum = 0);
    (n > 0);
    (i = 0);

    // loop body
    for (; i < n; i++)
    {
        int i2 = i * i;
        (y = (i * (i + 1) * (2 * i + 1) / 6));
        assert(sum == y);
        sum = sum + isqr(i);
    }

    // post-condition
    assert((sum == (n * (n + 1) * (2 * n + 1) / 6)));
}