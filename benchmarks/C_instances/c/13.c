int main()
{
  // variable declarations
  int x;
  int y;
  int z1;
  int z2;
  int z3;

  // scanf("%d", &x);
  // scanf("%d", &y);
  // pre-conditions
  assume((x >= 0));
  assume((x <= 2));
  assume((y <= 2));
  assume((y >= 0));
  // precheck
  // loopcond : unknown()
  // loopstart
  while (unknown())
  // loop body
  {
    {
      (x = (x + 2));
      (y = (y + 2));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((x == 4))
    assert((y != 0));
}
