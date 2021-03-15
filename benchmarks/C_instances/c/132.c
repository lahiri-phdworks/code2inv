
int main()
{
    int i = 0;
    int j, c, t;
    assume((c >= 40 && c <= 60));
    while (unknown())
    {
        if (c > 48)
        {
            if (c < 57)
            {
                j = i + i;
                t = c - 48;
                i = j + t;
            }
        }
    }
    assert(i >= 0);
}
