int main() {
  // variable declarations
  int c;
  int n;
  int v1;
  int v2;
  int v3;

  // scanf("%d", &c);
  // scanf("%d", &n);
  // pre-conditions
  assume((-10000 <= n && n <= 10000));
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
        if ((c > n)) {
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
    assert((c <= n));
}
