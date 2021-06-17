#include <156.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag)                                                   \
  if (!cond)                                                                   \
    flag = 1;

#define assume(cond)                                                           \
  if (!cond)                                                                   \
    continue;

#define INV(a, b, r) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int a, long long int b,
              long long int r) {
  int f = preflag;
  aflcrash(INV(a, b, r), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "a", a, "b", b,
            "r", r);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_a,
               long long int temp_b, long long int temp_r, long long int a,
               long long int b, long long int r) {
  int f = loopflag;
  aflcrash(INV(a, b, r), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "a", temp_a,
            "b", temp_b, "r", temp_r);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "a", a, "b", b,
            "r", r);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, a, b, r)                                   \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "a",                                                                          \
                a, "b", b, "r", r);                                            \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

// void swap(int *xp, int *yp) {
//   int temp = *xp;
//   *xp = *yp;
//   *yp = temp;
// }

// int gcd(int a, int b) {
//   if (!a || !b)
//     return a | b;
//   unsigned shift = __builtin_ctz(a | b);
//   a >>= __builtin_ctz(a);
//   do {
//     b >>= __builtin_ctz(b);
//     if (a > b)
//       swap(&a, &b);
//     b -= a;
//   } while (b);
//   return a << shift;
// }

int main() {
  // variable declarations
  unsigned int fast_gcd;
  unsigned int shift;
  unsigned int r;
  unsigned int a;
  unsigned int b;
  // unsigned int x;
  // unsigned int y;

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
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n", "a", a, "b", b,
             "r", r);

    // pre-conditions
    a = buf[1];
    b = buf[2];
    shift = 0;
    r = 1;
    fast_gcd = 1;
    assume((a > 0));
    assume((b > 0));
    assume((r > 0));
    assume((a % r == 0));
    assume((b % r == 0));
    // Invariant using the GCD function.
    // precheck
    // loopcond : (b != a)

    if (choices > 105) {
      // pre-conditions
      // fprintf(fptr, "BEGIN : %d, %d, %d, %d, %d\n", a, b, x, y, r);
      assume((a > 0));
      assume((b > 0));
      assume((r > 0));
      assume((a % r == 0));
      assume((b % r == 0));
      if (fast_gcd) {
        shift = __builtin_ctz(a | b);
        a >>= __builtin_ctz(a);
      }
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, a, b, r);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(a, b, r));

      // Loop Condition
      if ((b != a)) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        // fprintf(fptr, "LOOP : %d, %d, %d, %d, %d\n", a, b, x, y, r);
        while ((b != a) && unroll--) {
          assume((loopflag == 0));
          unsigned int temp_a = a;
          unsigned int temp_b = b;
          unsigned int temp_r = r;
          // loop-body
          if (fast_gcd) {
            b >>= __builtin_ctz(b);
          }
          if (a > b) {
            a = a - b;
          } else {
            b = b - a;
          }
          loopcount++;
          loopcheck(fptr, vars, temp_a, temp_b, temp_r, a, b, r);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if (fast_gcd)
          a = a << shift;
        // fprintf(fptr, "POST : %d, %d, %d, %d, %d\n", a, b, x, y, r);
        postcount++;
        postcheck(fptr, vars, ((a % r == 0) && (b % r == 0)), a, b, r)
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