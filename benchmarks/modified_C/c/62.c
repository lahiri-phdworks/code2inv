long long int func(long long int a, long long int b)
{
  long long int c = 0;
  __asm__ __volatile__("addl %%ebx, %%eax;"
                       : "=c"(c)
                       : "a"(a), "b"(b));
  return c;
}

int main()
{
  // variable declarations
  long long int c;
  long long int n;
  long long int v1;
  long long int v2;
  long long int v3;
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
    long long int temp_c = c;
    long long int temp_n = n;
    {
      if (unknown())
      {
        if ((c != n))
        {
          c = func(c, 1);
        }
      }
      else
      {
        if ((c == n))
        {
          (c = 1);
        }
      }
    }
  }
  // loopend
  // postcheck
  // post-condition
  // post-condition
  if ((n > -1))
  {
    assert((c != n));
  }
}
