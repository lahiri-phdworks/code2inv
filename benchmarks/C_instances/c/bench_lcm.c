// void swap(int *xp, int *yp) {
//   int temp = *xp;
//   *xp = *yp;
//   *yp = temp;
// }

// https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C
int gcd(int a, int b) {
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

int lcm(int a, int b) { return a / gcd(a, b) * b; }

int main() {
  // variable declarations
  int a;
  int b;
  int x;
  int y;
  int start;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &b);
  (a = 10);
  (b = 15);
  (x = a);
  (y = b);
  (start = a);
  assume((a > 0));
  assume((b > 0));
  // precheck
  // loopcond : (a != b)
  // loopstart
  while (start % b != 0) {
    start += a;
  }
  // loopend
  // postcheck
  // post-condition
  printf("%d\n", start);
  assert((a >= 0) && (b >= 0) && (start == lcm(x, y)));
}