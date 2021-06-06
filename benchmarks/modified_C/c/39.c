long long int func(long long int a, long long int b) {
  long long int c = 0;
  __asm__ __volatile__("addl %%ebx, %%eax;" : "=c"(c) : "a"(a), "b"(b));
  return c;
}

int main() {
  // variable declarations
  long long int n;
  long long int c;

  // pre-conditions
  // scanf("%d", &c);
  // scanf("%d", &n);
  (c = 0);
  assume((n > 0));
  // precheck
  // loopcond : (unknown())
  // loopstart
  while (unknown())
  // loop body
  {
    // long long int temp_c = c;
    // long long int temp_n = n;
    if (c == n) {
      c = 1;
    } else {
      c = func(c, 1);
    }
  }
  // loopend
  // postcheck
  // post-condition
  if (c == n) {
    // assert( c >= 0);
    assert(c <= n);
  }
}
