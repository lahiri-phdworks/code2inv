int main() {
  // variable declarations
  int c;
  int x1;
  int x2;
  int x3;
  int y;
  int z;
  // pre-conditions
  // scanf("%d", &y);
  assume((y >= 0));
  assume((y >= 127));
  (c = 0);
  (z = (36 * y));
  // precheck
  // loopcond : (unknown())
  // loopstart
  while (unknown())
  // loop body
  {
    if ((c < 36)) {
      (z = (z + 1));
      (c = (c + 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((c < 36))
    assert((z < 4608));
}
