// https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C
int remainder(int a, int d) {
  int quo, rem;
  __asm__("movl $0x0, %%edx;"
          "movl %2, %%eax;"
          "movl %3, %%ebx;"
          "idivl %%ebx;"
          : "=a"(quo), "=d"(rem)
          : "g"(a), "g"(d));
  return rem;
}

int main() {
  // variable declarations
  unsigned int q;
  unsigned int r;
  unsigned int a;
  unsigned int d;
  // pre-conditions
  // scanf("%d", &a);
  // scanf("%d", &d);
  // scanf("%d", &r);
  // scanf("%d", &q);
  (a = 7454);
  (d = 13);
  (r = a);
  (q = 0);
  assume((a >= 0));
  assume((d > 0));
  // precheck
  // loopcond : (r >= d)
  // loopstart
  while (r >= d) {
    q = q + 1;
    r = r - d;
  }
  // loopend
  // postcheck
  // post-condition
  assert((0 <= r <= d) && (a / d == q) && (r == remainder(a, d)));
}