int main()
{
  // variable declarations
  int x;
  int y;

  // scanf("%d", &y);
  // scanf("%d", &x);
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
  // post-condition
  // postcheck
  if ((y == 0))
    assert((x != 4));
}
