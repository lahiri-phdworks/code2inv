int isprime(int n)
{
}

int main()
{
    // variable declarations
    int n;
    int i;
    int out;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &i);
    // scanf("%d", &out);
    assume((n > 2));
    (i = 0);
    (out = 0);
    // precheck
    // loopcond : (i < n)
    // loopstart
    while ((i < n))
    {
        // loop body
        // int temp_n = n;
        // int temp_i = i;
        // int temp_out = out;
        i = i + 1;
        if (isprime(n))
        {
            out = out + 1;
        }
        else
        {
            out = out + 2;
        }
        // temp_n, temp_i, temp_out
    }
    // loopend
    // postcheck
    // post-condition
    if ((i % 2 == 0) || (i == 5))
    {
        assert(((i % 2 == 0) && (out == 2 * n)) || ((i == 5) && (out == 5)));
    }
}