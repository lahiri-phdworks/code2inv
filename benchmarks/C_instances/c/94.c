int main()
{
  // variable declarations
  int i;
  int j;
  int k;
  int n;

  // scanf("%d", &k);
  // scanf("%d", &n);
  // pre-conditions
  assume((-10000 <= k && k <= 10000));
  assume((-10000 <= n && n <= 10000));
  (i = 0);
  (j = 0);
  // precheck
  // loopcond : (i <= n)
  // loopstart
  while ((i <= n))
  // loopend
  // postcheck
  // post-condition
  {
    {
      (i = (i + 1));
      (j = (j + i));
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert(((i + (j + k)) > (2 * n)));
}
