
int main()
{
    int n;
    int y;
    int x = 1;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &y);
    assume((-10000 <= y && y <= 10000));
    assume((-10000 <= n && n <= 10000));
    // precheck
    // loopcond : (x <= n)
    // loopstart
    while (x <= n)
    // loop body
    {
        y = n - x;
        x = x + 1;
    }
    // loopend
    // postcheck
    // post-condition
    if (n > 0)
    {
        // assert (y >= 0);
        assert(y <= n);
    }
}
