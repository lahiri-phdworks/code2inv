int main()
{
  // variable declarations
  int n;
  int v1;
  int v2;
  int v3;
  int x;
  // pre-conditions
  (x = n);
  assume((-10000 <= x && x <= 10000));
  // loop body
  while ((x > 1))
  {
    {
      (x = (x - 1));
    }
  }
  // post-condition
  if ((n >= 0))
    assert((x == 1));
}
