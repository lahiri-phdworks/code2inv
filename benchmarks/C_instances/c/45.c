int main() {
  // variable declarations
  int c;
  int n;
  // pre-conditions
  // scanf("%d", &n);
  (c = 0);
  assume((n > 0));
  // precheck
  // loopcond : (unknown())
  // loopstart
  while (unknown())
  // loop body
  {
    {
      if (unknown()) {
        if ((c != n)) {
          (c = (c + 1));
        }
      } else {
        if ((c == n)) {
          (c = 1);
        }
      }
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((c != n))
    assert((c >= 0));
}
