int main() {
  // variable declarations
  unsigned int r;
  unsigned int a;
  unsigned int b;
  // pre-conditions
  assume((a > 0));
  assume((b > 0));
  assume((r > 0));
  assume((a % r == 0));
  assume((b % r == 0));
  // precheck
  // loop-cond : (a != b)
  // loopstart
  while (a != b) {
    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }
  }
  // post-condition
  assert((a % r == 0) && (b % r == 0));
}