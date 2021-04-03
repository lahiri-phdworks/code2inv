int main()
{
    // variable declarations
    int a, m, j, k;

    // scanf("%d", &m);
    // scanf("%d", &a);
    // pre-conditions
    assume((-10000 <= m && m <= 10000));
    assume((-10000 <= a && a <= 10000));
    assume(a <= m);
    assume(j < 1);
    (k = 0);
    // precheck
    // loopcond : (k < 1)
    // loopstart
    while (k < 1)
    // loop body
    {
        if (m < a)
        {
            m = a;
        }
        k = k + 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert(a >= m);
}
