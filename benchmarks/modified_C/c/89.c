int main()
{
  // variable declarations
  int lock;
  int v1;
  int v2;
  int v3;
  int x;
  int y;

  // scanf("%d", &y);
  // pre-conditions
  assume((-10000 <= y && y <= 10000));
  (x = y);
  (lock = 1);
  // precheck
  // loopcond : (x != y)
  // loopstart
  while ((x != y))
  // loop body
  {
    {
      if (unknown())
      {
        {
          (lock = 1);
          (x = y);
        }
      }
      else
      {
        {
          (lock = 0);
          (x = y);
          (y = (y + 1));
        }
      }
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert((lock == 1));
}
