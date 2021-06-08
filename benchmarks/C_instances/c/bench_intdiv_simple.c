int main() {
  // variable declarations
  int q;
  int r;
  int a;
  int d;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &d);
  // scanf("%d", &r);
  // scanf("%d", &q);
  (a = 7454);
  (d = 13);
  (r = a);
  (q = 0);
  assume((d != 0));
  // precheck
  // loopcond : (r >= d)
  // loopstart
  while (r >= d) {
    q = q + 1;
    r = r - d;
  }
  // loopend
  // postcheck
  // post-condition
  assert((0 <= r <= d) && (a / d == q));
}