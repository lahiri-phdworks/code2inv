#include <assert.h>
#include <bench_lcm.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 32

#define aflcrash(cond, flag)                                                   \
  if (!cond)                                                                   \
    flag = 1;

#define assume(cond)                                                           \
  if (!cond)                                                                   \
    continue;

#define INV(a, b, y, start) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int a, long long int b,
              long long int y, long long int start) {
  int f = preflag;
  aflcrash(INV(a, b, y, start), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a,
            "b", b, "y", y, "start", start);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_a,
               long long int temp_b, long long int temp_y,
               long long int temp_start, long long int a, long long int b,
               long long int y, long long int start) {
  int f = loopflag;
  aflcrash(INV(a, b, y, start), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "a", temp_a, "b", temp_b, "y", temp_y, "start", temp_start);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a",
            a, "b", b, "y", y, "start", start);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, a, b, y, start)                            \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "a",                                                                          \
                a, "b", b, "y", y, "start", start);                            \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

void swap(int *term1, int *term2) {
  int temp = *term1;
  *term1 = *term2;
  *term2 = temp;
}

int gcd(int a, int b) {

  if (a == 0 || b == 0)
    return 0;

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

int lcm(int a, int b) {

  if (a == 0 || b == 0)
    return 0;

  return a / gcd(a, b) * b;
}

int main() {
  // variable declarations
  int a;
  int b;
  int x;
  int y;
  int start;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const uint8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a,
             "b", b, "y", y, "start", start);

    // pre-conditions
    a = buf[1];
    b = buf[2];
    start = a;
    x = a;
    y = b;

    // HonggFuzz Specific Assume
    assume(a > 0);
    assume(b > 0);

    // Invariant using the GCD function.
    // precheck
    // loopcond : (start % b != 0)
    // fprintf(fptr, "%d, %d, %d, %d, %d\n", a, b, x, y, choices);

    if (choices > 100) {
      // pre-conditions
      a = 514231;
      b = 236569;
      x = a;
      y = b;
      start = a;
      assume((a > 0));
      assume((b > 0));
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, a, b, y, start);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(a, b, y, start));

      // Loop Condition
      if (start % b != 0) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((start % b != 0) && unroll--) {
          assume((loopflag == 0));
          int temp_a = a, temp_b = b, temp_y = y, temp_start = start;

          // loop body
          // (start % a == 0)
          start += a;

          loopcount++;
          loopcheck(fptr, vars, temp_a, temp_b, temp_y, temp_start, a, b, y,
                    start);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        printf("%d\n", start);
        postcount++;
        postcheck(fptr, vars, ((a >= 0) && (b >= 0) && (start == lcm(x, y))), a,
                  b, y, start)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100) {
      fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount,
              "loopcount", loopcount, "postcount", postcount);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3) {
      fclose(fptr);
      assert(0);
    }
  }

  fclose(fptr);
  return 0;
}
