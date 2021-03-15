int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;
  // pre-conditions
  (j = 0);
  (i = 0);
  (y = 2);
  // loop body
  assume((-10000 <= x && x <= 10000));
  assume((-10000 <= y && y <= 10000));

  while ((i <= x))
  {
    {
      (i = (i + 1));
      (j = (j + y));
    }
  }
  // post-condition
  if ((i != j))
    assert((y != 1));
}
