int main()
{
  // variable declarations
  int n;
  int x;
  int y;

  // scanf("%d", &n);
  // pre-conditions
  assume((-10000 <= n && n <= 10000));
  (x = n);
  (y = 0);
  // precheck
  // loopcond : (x > 0)
  // loopstart
  while ((x > 0))
  // loop body
  {
    {
      (y = (y + 1));
      (x = (x - 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert((y == n));
}
