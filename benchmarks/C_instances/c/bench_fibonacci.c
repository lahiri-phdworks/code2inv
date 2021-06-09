double fib(double n) {
  double phi = (1 + sqrt(5)) / 2;
  return round(pow(phi, n) / sqrt(5));
}

int main() {
  // variable declarations
  unsigned int x;
  unsigned int y;
  unsigned int i;
  double n;
  // pre-conditions
  // scanf("%d", &x);
  // scanf("%d", &y);
  // scanf("%d", &n);
  // scanf("%d", &i);
  (x = 0);
  (y = 1);
  (n = 10);
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
  assert((0 <= i) && (i <= n) && (n >= 0) && (x == (int)fib(i)) &&
         (y == (int)fib(i + 1)));
}