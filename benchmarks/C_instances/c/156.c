int main() {
  // variable declarations
  unsigned int r;
  unsigned int a;
  unsigned int b;
  // unsigned int x;
  // unsigned int y;
  // pre-conditions
  // assume((x > 0));
  // assume((y > 0));
  assume((a > 0));
  assume((b > 0));
  assume((r > 0));
  assume((a % r == 0));
  assume((b % r == 0));
  // (x = a);
  // (y = b);
  // (r = 1);
  // loop
  while (b != 0) {
    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }
  }
  r = a;
  // post
  assert((a % r == 0) && (r > 0));
}