
int main()
{
    // variable declarations
    int z1;
    int z2;
    int z3;
    int x;
    int m;
    int n;

    // scanf("%d", &n);
    // scanf("%d", &x);
    // scanf("%d", &m);
    // pre-conditions
    (x = 1);
    (m = 1);
    assume((-10000 <= m && m <= 10000));
    assume((-10000 <= x && x <= 10000));
    assume((-10000 <= n && n <= 10000));
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
    // post-condition
    if (n > 1)
    {
        assert(m < n);
    }
}
