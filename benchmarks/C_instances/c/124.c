int main() {
  // variable declarations
  int i;
  int j;
  int x;
  int y;

  // scanf("%d", &x);
  // scanf("%d", &y);
  // pre-conditions
  assume((-10000 <= y && y <= 10000));
  assume((-10000 <= x && x <= 10000));
  (i = x);
  (j = y);
  // precheck
  // loopcond : (x != 0)
  // loopstart
  while ((x != 0))
  // loop body
  {
    {
      (x = (x - 1));
      (y = (y - 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((i == j))
    assert((y == 0));
}
