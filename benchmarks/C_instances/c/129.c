int main()
{
  // variable declarations
  int x;
  int y;
  int z1;
  int z2;
  int z3;
  // pre-conditions
  (x = 1);
  assume((-10000 <= y && y <= 10000));
  // loop body
  while ((x < y))
  {
    {
      (x = (x + x));
    }
  }
  // post-condition
  assert((x >= 1));
}
