int main() {
  // variable declarations
  int x = 0;
  int y;
  int z;
  // pre-conditions
  // scanf("%d", &y);
  // scanf("%d", &z);
  assume((-10000 <= y && y <= 10000));
  assume((-10000 <= z && z <= 10000));
  // precheck
  // loopcond : (x < 500)
  // loopstart
  while (x < 500)
  // loop body
  {
    x += 1;
    if (z <= y) {
      y = z;
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert(z >= y);
}
