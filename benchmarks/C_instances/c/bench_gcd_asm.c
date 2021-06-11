// void swap(int *xp, int *yp) {
//   int temp = *xp;
//   *xp = *yp;
//   *yp = temp;
// }

// https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C
int asmgcd(int a, int b) {
  int result;
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
  return result;
}

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
  /* Compute Greatest Common Divisor using Euclid's Algorithm */
  while (a != b) {
    if (a > b) {
      swap(&a, &b);
    }
    b = b - a;
  }
  // loopend
  // postcheck
  // post-condition
  assert((a >= 0) && (b >= 0) && (a == asmgcd(x, y)));
}