int main()
{
  // variable declarations
  int x;

  // scanf("%d", &x);
  // pre-conditions
  (x = 100);
  // precheck
  // loopcond : (x > 0)
  // loopstart
  while ((x > 0))
  // loop body
  {
    {
      (x = (x - 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert((x == 0));
}
