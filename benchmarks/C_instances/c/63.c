
int main()
{
    // variable declarations
    int x;
    int y;

    // scanf("%d", &x);
    // pre-conditions
    (x = 1);
    // precheck
    // loopcond : (x <= 10)
    // loopstart
    while (x <= 10)
    // loop body
    {
        y = 10 - x;
        x = x + 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert(y >= 0);
}
