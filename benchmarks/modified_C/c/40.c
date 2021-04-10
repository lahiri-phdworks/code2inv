long long int func(long long int lhs, long long int rhs)
{
  return lhs >= rhs ? 1 : 0;
}

long long int pow(long long int x, long long int y)
{
  return 0;
}

int main()
{
  // variable declarations
  long long int c;
  long long int n;

  // pre-conditions
  // scanf("%d", &c);
  // scanf("%d", &n);
  (c = 0);
  assume((n > 0));
  // precheck
  // loopcond : (unknown())
  // loopstart
  while (unknown())
  // loop body
  {
    // long long int temp_c = c;
    // long long int temp_n = n;
    {
      if (unknown())
      {
        if ((c > n))
        {
          (c = (c + 1));
        }
      }
      else
      {
        if ((c == n))
        {
          (c = pow(n, 2));
        }
      }
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((c == n))
  {
    assert((c == pow(n, 2)));
  }
}
