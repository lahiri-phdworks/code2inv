#include "assert.h"

/**
 * Sum of the first "n" natural numbers 
 * 1, 2, 3, .... n
 * Only natural numbers strictly.
*/

int main()
{
    // variable declarations
    int sum;
    int n;
    int i;
    int y;
    int i2;

    // pre-conditions
    (i = 0);
    (sum = 0);
    __VERIFIER_assume((n > 0));

    // loop body
    for (; i <= n; i++)
    {
        (i2 = i * i);
        (y = (i * (i + 1) * (2 * i + 1) / 6));

        // assert(sum == y);
        (sum = sum + i2);
    }

    // post-condition
    __VERIFIER_assert((sum == (n * (n + 1) * (2 * n + 1) / 6)));
}