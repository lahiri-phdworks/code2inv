#include <assert.h>
#include <bench_gcd.h>
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

#define INV(a, b, x, y) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int a, long long int b,
              long long int x, long long int y) {
  int f = preflag;
  aflcrash(INV(a, b, x, y), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a,
            "b", b, "x", x, "y", y);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_a,
               long long int temp_b, long long int temp_x, long long int temp_y,
               long long int a, long long int b, long long int x,
               long long int y) {
  int f = loopflag;
  aflcrash(INV(a, b, x, y), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "a", temp_a, "b", temp_b, "x", temp_x, "y", temp_y);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a",
            a, "b", b, "x", x, "y", y);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, a, b, x, y)                                \
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
                a, "b", b, "x", x, "y", y);                                    \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

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
  unsigned int a;
  unsigned int b;
  unsigned int x;
  unsigned int y;

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
             "b", b, "x", x, "y", y);

    // pre-conditions
    a = buf[1];
    b = buf[2];
    x = a;
    y = b;
    // Invariant using the GCD function.
    // precheck
    // loopcond : (a != b)

    if (choices > 100) {
      // pre-conditions
      a = 514231;
      b = 236569;
      x = a;
      y = b;
      assume((a >= 0));
      assume((b >= 0));
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, a, b, x, y);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(a, b, x, y));
      /* Compute Greatest Common Divisor using Euclid's Algorithm */

      // Loop Condition
      if ((a != b)) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((a != b) && unroll--) {
          assume((loopflag == 0));
          int temp_a = a, temp_b = b, temp_x = x, temp_y = y;

          // loop body
          if (a > b) {
            swap(&a, &b);
          }
          b = b - a;

          loopcount++;
          loopcheck(fptr, vars, temp_a, temp_b, temp_x, temp_y, a, b, x, y);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, ((a >= 0) && (b >= 0) && (a == gcd(x, y))), a, b,
                  x, y)
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