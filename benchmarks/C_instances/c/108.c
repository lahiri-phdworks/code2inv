
int main() {
  // variable declarations
  int a, c, m, j, k;

  // scanf("%d", &c);
  // scanf("%d", &a);
  // pre-conditions
  assume((-10000 <= c && c <= 10000));
  assume((-10000 <= a && a <= 10000));
  assume(a <= m);
  (j = 0);
  (k = 0);
  // precheck
  // loopcond : (k < c)
  // loopstart
  while (k < c)
  // loop body
  {
    if (m < a) {
      m = a;
    }
    k = k + 1;
  }
  // loopend
  // postcheck
  // post-condition
  assert(a <= m);
}
