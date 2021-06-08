int main() {
  // variable declarations
  int n;
  int v1;
  int v2;
  int v3;
  int x;
  int y;

  // scanf("%d", &n);
  // pre-conditions
  (x = 1);
  // precheck
  // loopcond : (x <= n)
  // loopstart
  while (x <= n)
  // loop body
  {
    y = n - x;
    x = x + 1;
  }
  // loopend
  // postcheck
  // post-condition
  if (n > 0) {
    // assert (y >= 0);
    assert(y < n);
  }
}
