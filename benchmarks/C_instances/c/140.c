int main() {
  // variable declarations
  long long int sum;
  long long int n;
  long long int i;
  // long long int y;
  // long long int i2;
  // pre-conditions
  // scanf("%d", &n);
  assume((n > 0));
  assume((n < 5000));
  (sum = 0);
  (i = 0);
  // (i2 = 0);
  // (y = 0);
  // precheck
  // loopcond : (i < n)
  // loopstart
  while (i < n)
  // loop body
  {
    i = i + 1;
    // (i2 = i * i);
    // (y = (i * (i + 1) * (2 * i + 1)) / (6));
    sum = sum + (i * i);
  }
  // loopend
  // postcheck
  // post-condition
  assert((sum == ((n * (n + 1) * (2 * n + 1)) / (6))));
}