int main()
{
  // variable declarations
  int i;
  int sn;

  // scanf("%d", &i);
  // pre-conditions
  assume((-10000 <= i && i <= 10000));
  (sn = 0);
  (i = 1);
  // precheck
  // loopcond : (i <= 8)
  // loopstart
  while ((i <= 8))
  // loop body
  {
    {
      (i = (i + 1));
      (sn = (sn + 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((sn != 0))
    assert((sn == 8));
}
