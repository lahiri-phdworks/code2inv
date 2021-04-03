int incr1(int a, int b)
{
  return b + a;
}

int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;

  // scanf("%d", &i);
  // scanf("%d", &y);
  // pre-conditions
  (j = 0);
  (i = 0);
  (y = 1);
  // precheck
  // loopcond : (i <= x)
  // loopstart
  while ((i <= x))
  // loop body
  {
    {
      (i = incr1(i, 1));
      (j = (j + y));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((y == 1))
    assert((i == j));
}
