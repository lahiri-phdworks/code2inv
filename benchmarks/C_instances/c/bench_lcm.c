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

int lcm(int a, int b) { return a / gcd(a, b) * b; }

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
  assume((a > 0));
  assume((b > 0));
  // precheck
  // loopcond : (a != b)
  // loopstart
  while (a != b) {
    if (a > b)
      swap(&a, &b);
    b -= a;
  }
  // loopend
  // postcheck
  // post-condition
  assert((a >= 0) && (b >= 0) && (((x * y) / a) == lcm(x, y)));
}