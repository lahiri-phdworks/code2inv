int main() {
  // variable declarations
  int x;
  int y;
  int a;
  int d;
  int result;
  int y_power;
  int power;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &d);
  // scanf("%d", &x);
  // scanf("%d", &y);
  (a = 7454);
  (d = 13);
  (x = a);
  (y = d);
  assume((d != 0));
  (power = 31);
  (result = 0);
  (y_power = y << power);
  // precheck
  // loopcond : (x >= y)
  // loopstart
  while (x >= y) {
    // loop body
    while (y_power > x) {
      y_power >>= 1;
      power -= 1;
    }
    result += 1 << power;
    x -= y_power;
  }
  // loopend
  // postcheck
  // post-condition
  assert((0 <= x < d) && (a == result * d + x));
}