int main()
{
  // variable declarations
  int x;
  int y;

  // scanf("%d", &y);
  // pre-conditions
  (x = 1);
  (y = 0);
  assume((-10000 <= x && x <= 10000));
  assume((-1000 <= y && y <= 1000));
  assume((x == 1));
  assume((y == 0));
  // precheck
  // loopcond : (y < 1000)
  // loopstart
  while ((y < 1000))
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
