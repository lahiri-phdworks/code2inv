// https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C
double square_root(double x) {
  __asm__("fsqrt" : "+t"(x));
  return x;
}

int main() {
  // variable declarations
  int left;
  int right;
  int mid;
  unsigned int n;
  // pre-conditions
  // scanf("%d", &n);
  // scanf("%d", &left);
  // scanf("%d", &right);
  (n = 745);
  (left = 0);
  (right = n);
  assume((n > 0));
  // precheck
  // loopcond : (left <= right)
  // loopstart
  while (left <= right) {
    // loop body
    mid = (left + right) / 2;
    if (mid * mid <= n)
      left = mid + 1;
    else
      right = mid - 1;
  }
  // loopend
  // postcheck
  // post-condition
  assert(round(square_root(n)) == left - 1);
}