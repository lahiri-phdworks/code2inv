int main() {
  // variable declarations
  long long int a;
  long long int b;
  double x;
  double y;
  long long res;
  // pre-conditions
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
  // printf("%d, %d, %d, %d\n", res, (int)pow(x, y), a, b);
  assert((a >= 0) && (b >= 0) && (res == (int)pow(x, y)));
}