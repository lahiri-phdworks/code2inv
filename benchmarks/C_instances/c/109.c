
int main() {
  // variable declarations
  int a;
  int c;
  int m;
  int j;
  int k;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &c);
  // scanf("%d", &m);
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
  if (c > 0) {
    assert(a <= m);
  }
}
