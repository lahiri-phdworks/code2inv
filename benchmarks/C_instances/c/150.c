int main()
{
    int arr[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        9, 9, 9, 9, 9, 9, 9, 9, 9, 9};

    // variable declarations
    int sum;
    int n;
    int i;
    int index;
    // pre-conditions
    // scanf("%d", &n);

    (sum = 0);
    (i = 0);
    (n = 100);
    (index = 0);

    // precheck
    // loopcond : (i < n)
    // loopstart
    while (index < n)
    // loop body
    {
        index = index + 1;
        sum = sum + arr[index];
    }
    // loopend
    // postcheck
    // post-condition
    assert((sum == 450));
}