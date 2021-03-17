int main()
{
  // variable declarations
  int x;
  int y;

  // scanf("%d", &x);
  // scanf("%d", &y);
  // pre-conditions
  (x = 1);
  (y = 0);
  assume((x == 1));
  assume((y == 0));
  // precheck
  // loopcond : (y < 100000)
  // loopstart
  while ((y < 100000))
  // loop body
  {
    {
      (x = (x + y));
      (y = (y + 1));
    }
  }
  // loopend
  // postcheck
  assert((x >= y));
}
