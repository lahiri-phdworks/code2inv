long long int func(long long int a, long long int b)
{
  return a + b;
}

int main()
{
  // variable declarations
  long long int c;
  long long int x1;
  long long int x2;
  long long int x3;
  long long int y;
  long long int z;
  // pre-conditions
  // scanf("%d", &c);
  // scanf("%d", &y);
  // scanf("%d", &z);
  (c = 0);
  assume((y >= 0));
  assume((y >= 127));
  (z = (36 * y));
  // precheck
  // loopcond : (unknown())
  // loopstart
  while (unknown())
  {
    // loop body
    // long long int temp_c = c;
    // long long int temp_y = y;
    // long long int temp_z = z;
    if ((c < 36))
    {
      z = func(z, 1);
      c = func(c, 1);
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((c < 36))
  {
    assert((z >= 0));
  }
}
