int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;
  // pre-conditions
  // scanf("%d", &y);
  // scanf("%d", &x);
  // scanf("%d", &i);
  (j = 0);
  (i = 0);
  (y = 2);
  // precheck
  // loopcond : (i <= x)
  // loopstart
  while ((i <= x))
  // loop body
  {
    {
      (i = (i + 1));
      (j = (j + y));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((i != j))
    assert((y != 1));
}
