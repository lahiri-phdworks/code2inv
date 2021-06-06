long long int func(long long int a, long long int b) {
  long long int c = 0;
  __asm__ __volatile__("addl %%ebx, %%eax;" : "=c"(c) : "a"(a), "b"(b));
  return c;
}

int main() {
  // variable declarations
  long long int c;

  // scanf("%d", &c);
  // pre-conditions
  (c = 0);
  // precheck
  // loopcond : (unknown())
  // loopstart
  while (unknown())
  // loop body
  {
    // long long int temp_c = c;
    {
      if (unknown()) {
        if ((c != 40)) {
          c = func(c, 1);
        }
      } else {
        if ((c == 40)) {
          (c = 1);
        }
      }
    }
  }
  // loopend
  // postcheck
  // post-condition
  if ((c != 40)) {
    assert((c <= 40));
  }
}
