static int f[100003];

int factmod(int n, int p) {
  if (n >= p)
    return 0;
  int res = 1;
  while (n > 1) {
    if ((n / p) % 2)
      res = p - res;
    res = res * f[n % p] % p;
    n /= p;
  }
  return res;
}

int main() {
  // variable declarations
  int f[100003];
  unsigned int n;
  unsigned int p;
  unsigned long long int r;
  unsigned int k;
  // pre-conditions
  // scanf("%d", &n);
  (r = 1LL);
  (k = 0);
  (n = 32);
  (p = 100003);

  f[0] = 1;
  for (int i = 1; i < p; i++)
    f[i] = f[i - 1] * i % p;
  // precheck
  // loopcond : (k != n)
  // loopstart
  while (k != n) {
    // loopbody
    k = k + 1;
    r = (r * k) % p;
  }
  // loopend
  // postcheck
  // post-condition
  assert((n >= 0) && (k >= 0) && (r == factmod(n, 100003)));
}