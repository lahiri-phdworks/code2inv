void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int gcd(int a, int b) {
  if (!a || !b)
    return a | b;
  unsigned shift = __builtin_ctz(a | b);
  a >>= __builtin_ctz(a);
  do {
    b >>= __builtin_ctz(b);
    if (a > b)
      swap(&a, &b);
    b -= a;
  } while (b);
  return a << shift;
}

int main() {
  // variable declarations
  int a;
  int b;
  int x;
  int y;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &b);
  (a = 5);
  (b = 7);
  (x = a);
  (y = b);
  // Invariant using the GCD function.
  // precheck
  // loopcond : (a != b)
  // loopstart
  while (a != b) {
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  // loopend
  // postcheck
  // post-condition
  assert((a >= 0) && (b >= 0) && (a == gcd(x, y)));
}