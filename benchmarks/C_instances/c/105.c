int main()
{
  // variable declarations
  int n;
  int v1;
  int v2;
  int v3;
  int x;
  // pre-conditions
  (x = 0);
  assume((-10000 <= n && n <= 10000));
  // loop body
  while ((x < n))
  {
    {
      (x = (x + 1));
    }
  }
  // post-condition
  if ((n >= 0))
    assert((x == n));
}
