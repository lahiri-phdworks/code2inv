int main() {
  // variable declarations
  int x;
  int y;

  // pre-conditions
  // scanf("%d", &y);
  assume((-10000 <= x && x <= 10000));
  assume((-1000 <= y && y <= 1000));
  assume((x == 1));
  assume((y == 0));
  (x = 1);
  (y = 0);
  // precheck
  // loopcond : (y < 1000)
  // loopstart
  while ((y < 1000))
  // loop body
  {
    {
      (x = (x + y));
      (y = (y + 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert((x >= y));
}
