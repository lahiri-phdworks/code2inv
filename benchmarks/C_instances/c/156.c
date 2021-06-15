int main() {
  // variable declarations
  unsigned int a;
  unsigned int b;
  unsigned int x;
  unsigned int y;
  // pre-conditions
  (x = a);
  (y = b);
  assume((x > 0));
  assume((y > 0));
  assume((a > 0));
  assume((b > 0));
  // loop
  while (b != 0) {
    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }
  }
  // post
  assert((x % a == 0) && (y % a == 0));
}