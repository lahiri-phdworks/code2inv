
int main()
{
    int n;
    int c = 0;
    assume(n > 0);

    assume((-10000 <= n && n <= 10000));
    assume((-10000 <= c && c <= 10000));

    while (unknown())
    {
        if (c == n)
        {
            c = 1;
        }
        else
        {
            c = c + 1;
        }
    }

    if (c == n)
    {
        assert(c >= 0);
        //assert( c <= n);
    }
}
