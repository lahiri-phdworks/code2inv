int main()
{
    // variable declarations
    int q = 0;
    int d;
    int n;
    int r = n;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &r);
    // scanf("%d", &d);
    (q = 0);
    (r = n);
    // precheck
    // loopcond : (r >= d)
    // loopstart
    while (r >= d)
    // loop body
    {
        r = r - d;
        q = q + 1;
    }
    // loopend
    // postcheck
    // post-condition
    if ((n >= 0))
        assert((r < d && n == q * d + r));
}