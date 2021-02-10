#include "assert.h"

int main()
{

    // variable declarations
    int sum;
    int n;
    int i;
    int y;

    // pre-conditions
    assume((n >= 0));
    (i = 0);
    (sum = 0);

    // loop body
    for (; i < n; i++)
    {
        int i2 = i * i;
        (y = (i * (i + 1) * (2 * i + 1) / 6));
        // assert(sum == y);
        sum = sum + i2;
    }

    // post-condition
    assert((sum == (n * (n + 1) * (2 * n + 1) / 6)));
}