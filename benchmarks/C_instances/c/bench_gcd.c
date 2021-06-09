// void swap(int *xp, int *yp) {
//   int temp = *xp;
//   *xp = *yp;
//   *yp = temp;
// }

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

// https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C
int main() {
  // variable declarations
  unsigned int a;
  unsigned int b;
  unsigned int x;
  unsigned int y;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &b);
  (a = 514231);
  (b = 236569);
  (x = a);
  (y = b);
  assume((a >= 0));
  assume((b >= 0));
  // Invariant using the GCD function.
  // precheck
  // loopcond : (a != b)
  // loopstart
  while (a != b) {
    if (a > b) {
      swap(&a, &b);
    }
    b = b - a;
  }
  // loopend
  // postcheck
  // post-condition
  assert((a >= 0) && (b >= 0) && (a == gcd(x, y)));
}