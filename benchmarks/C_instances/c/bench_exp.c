int main() {
  // variable declarations
  int a;
  int b;
  int x;
  int y;
  long long res;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &b);
  // scanf("%d", &res);
  (a = 5);
  (b = 3);
  (x = a);
  (y = b);
  (res = 1);
  // precheck
  // loopcond : (b > 0)
  // loopstart
  while (b > 0) {
    // loop body
    if (b & 1)
      res = res * a;
    a = a * a;
    b >>= 1;
  }
  // loopend
  // postcheck
  // post-condition
  assert((a >= 0) && (b >= 0) && (res == pow(x, y)));
}