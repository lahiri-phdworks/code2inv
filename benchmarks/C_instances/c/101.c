int main()
{
  // variable declarations
  int n;
  int x;

  // scanf("%d", &n);
  // pre-conditions
  assume((-10000 <= n && n <= 10000));
  (x = 0);
  // precheck
  // loopcond : (x < n)
  // loopstart
  while ((x < n))
  // loop body
  {
    {
      (x = (x + 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((x != n))
    assert((n < 0));
}
