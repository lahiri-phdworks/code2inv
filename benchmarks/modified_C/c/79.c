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
  long long int i;
  long long int x;
  long long int y;
  // pre-conditions
  // scanf("%d", &i);
  // scanf("%d", &x);
  // scanf("%d", &y);
  (i = 0);
  assume((x >= 0));
  assume((y >= 0));
  assume((x >= y));
  // precheck
  // loopcond : (unknown())
  // loopstart
  while (unknown())
  // loop body
  {
    long long int temp_i = i;
    long long int temp_x = x;
    long long int temp_y = y;
    if ((i < y))
    {
      (i = (func(i, 1)));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((i >= x))
  {
    if ((0 > i))
    {
      assert((i >= y));
    }
  }
}
