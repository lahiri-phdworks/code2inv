int main() {
  // variable declarations
  int i;
  int x;
  int y;
  int z1;
  int z2;
  int z3;

  // scanf("%d", &y);
  // pre-conditions
  assume((-10000 <= y && y <= 10000));
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
    if ((i < y)) {
      (i = (i + 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((i < y))
    assert((i < x));
}
