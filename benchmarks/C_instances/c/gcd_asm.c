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

int main() {
  // variable declarations
  int a;
  int b;
  int x;
  int y;
  int result;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &b);
  (a = 514231);
  (b = 236569);
  (x = a);
  (y = b);
  // Invariant using the GCD function.
  // precheck
  // loopcond : (a != b)
  // loopstart
  /* Compute Greatest Common Divisor using Euclid's Algorithm */
  __asm__ __volatile__("movl %1, %%eax;"
                       "movl %2, %%ebx;"
                       "CONTD: cmpl $0, %%ebx;"
                       "je DONE;"
                       "xorl %%edx, %%edx;"
                       "idivl %%ebx;"
                       "movl %%ebx, %%eax;"
                       "movl %%edx, %%ebx;"
                       "jmp CONTD;"
                       "DONE: movl %%eax, %0;"
                       : "=g"(result)
                       : "g"(a), "g"(b));
  // loopend
  // postcheck
  // post-condition
  assert((a >= 0) && (b >= 0) && (result == gcd(x, y)));
}