int main()
{
  // variable declarations
  int x;
  int y;
  int z1;
  int z2;
  int z3;

  // scanf("%d", &y);
  // pre-conditions
  assume((-10000 <= y && y <= 10000));
  (x = -15000);
  // precheck
  // loopcond : (x < 0)
  // loopstart
  while ((x < 0))
  // loop body
  {
    {
      (x = (x + y));
      (y = (y + 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert((y > 0));
}
