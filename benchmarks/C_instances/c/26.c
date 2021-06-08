int main() {
  // variable declarations
  int n;
  int x;

  // scanf("%d", &n);
  // pre-conditions
  assume((-10000 <= n && n <= 10000));
  (x = n);
  // precheck
  // loopcond : (x > 1)
  // loopstart
  while ((x > 1))
  // loop body
  {
    { (x = (x - 1)); }
  }
  // loopend
  // postcheck
  // post-condition
  if ((x != 1))
    assert((n < 0));
}
