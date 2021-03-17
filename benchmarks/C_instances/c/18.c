
int main()
{
    int x;
    int m;
    int n;

    // scanf("%d", &x);
    // scanf("%d", &n);
    // pre-conditions
    assume((-10000 <= n && n < 10000));
    (x = 1);
    (m = 1);

    // precheck
    // loopcond : (x < n)
    // loopstart
    while (x < n)
    // loop body
    {
        if (unknown())
        {
            m = x;
        }
        x = x + 1;
    }
    // loopend
    // postcheck
    if (n > 1)
    {
        // assert (m < n);
        assert(m >= 1);
    }
}
