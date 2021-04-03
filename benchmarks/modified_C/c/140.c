int main()
{
    // variable declarations
    int sum;
    int n;
    int i;
    int y;
    int i2;
    // pre-conditions
    // scanf("%d", &n);
    assume((n > 0));
    assume((n < 500000));
    (sum = 0);
    (i = 1);
    (i2 = 0);
    // precheck
    // loopcond : (i <= n)
    // loopstart
    while (i <= n)
    // loop body
    {
        (i2 = i * i);
        (i = i + 1);
        (y = (i * (i + 1) * (2 * i + 1) / 6));
        sum = sum + i2;
    }
    // loopend
    // postcheck
    // post-condition
    assert((sum == (n * (n + 1) * (2 * n + 1) / 6)));
}