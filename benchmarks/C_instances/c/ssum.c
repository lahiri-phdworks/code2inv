int main()
{
    // variable declarations
    int sum;
    int n;
    int i;
    int y;
    int i2;

    // pre-conditions
    (sum = 0);
    (i = 1);
    assume((n > 0));

    // loop body
    for (i = 1; i <= n; i++)
    {
        (i2 = i * i);
        (y = (i * (i + 1) * (2 * i + 1) / 6));
        // assert(sum == y);
        sum = sum + i2;
    }

    assert((sum == (n * (n + 1) * (2 * n + 1) / 6)));
}