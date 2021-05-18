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

int main()
{
    // variable declarations
    long long int sum;
    long long int n;
    long long int i;
    long long int index;
    // pre-conditions
    // scanf("%d", &n);

    sum = 0;
    i = 0;
    n = 100;
    // precheck
    // loopcond : (i < n)
    // loopstart
    while (i < n)
    // loop body
    {
        i = i + 1;
        sum = sum + arr[i];
    }
    // loopend
    // postcheck
    // post-condition
    assert(sum == 450);
}