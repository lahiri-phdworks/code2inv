long long int func(long long int a, long long int b)
{
    long long int c = 0;
    __asm__ __volatile__("addl %%ebx, %%eax;"
                         : "=c"(c)
                         : "a"(a), "b"(b));
    return c;
}

int main()
{
    long long int z1, z2, z3;
    long long int x;
    long long int m;
    long long int n;

    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &m);
    // scanf("%d", &n);
    (x = 1);
    (m = 1);
    // precheck
    // loopcond : (x < n)
    // loopstart
    while (x < n)
    {
        // loop body
        // long long int temp_x = x;
        // long long int temp_m = m;
        // long long int temp_n = n;
        if (unknown())
        {
            m = x;
        }
        x = func(x, 1);
    }
    // loopend
    // postcheck
    // post-condition
    if (n > 1)
    {
        //assert (m < n);
        assert(m >= 1);
    }
}
