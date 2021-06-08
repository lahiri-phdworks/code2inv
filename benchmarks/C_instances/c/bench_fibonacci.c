int fib(int n) {
  double phi = (1 + sqrt(5)) / 2;
  return round(pow(phi, n) / sqrt(5));
}

int main() {
  // variable declarations
  int x;
  int y;
  int i;
  int n;
  // pre-conditions
  // scanf("%d", &x);
  // scanf("%d", &y);
  // scanf("%d", &n);
  // scanf("%d", &i);
  (x = 0);
  (y = 1);
  (n = 20);
  (i = 0);
  // precheck
  // loopcond : (i < n)
  // loopstart
  while (i < n) {
    // loop body
    // in-place output use in addition.
    asm("   movl    %2,%0;"
        "   addl    %1,%0;"
        : "=&r"(y)
        : "r"(x), "r"(y));
    x = y - x;
    i = i + 1;
  }
  // loopend
  // postcheck
  // post-condition
  assert((0 <= i < n) && (x == fib(i)) && (y == fib(i + 1)));
}