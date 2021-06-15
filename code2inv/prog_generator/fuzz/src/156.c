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

#define INV(a, b, x, y, r) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int a, long long int b,
              long long int x, long long int y, long long int r) {
  int f = preflag;
  aflcrash(INV(a, b, x, y, r), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr,
            "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "a", a, "b", b, "x", x, "y", y, "r", r);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_a,
               long long int temp_b, long long int temp_x, long long int temp_y,
               long long int temp_r, long long int a, long long int b,
               long long int x, long long int y, long long int r) {
  int f = loopflag;
  aflcrash(INV(a, b, x, y, r), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(
        fptr,
        "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
        "a", temp_a, "b", temp_b, "x", temp_x, "y", temp_y, "r", temp_r);
    fprintf(fptr,
            "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "a", a, "b", b, "x", x, "y", y, "r", r);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, a, b, x, y, r)                             \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(                                                               \
          fptr,                                                                \
          "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "a",                                                                          \
          a, "b", b, "x", x, "y", y, "r", r);                                  \
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
  unsigned int a;
  unsigned int b;
  unsigned int x;
  unsigned int y;
  unsigned int r;

  char buff[2048];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 2048);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const uint8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    int choices = buf[0];

    char vars[150];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 150,
             "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a,
             "b", b, "x", x, "y", y, "r", r);

    // pre-conditions
    a = buf[1];
    b = buf[2];
    shift = 0;
    r = 1;
    fast_gcd = 1;
    x = a;
    y = b;
    assume((a > 0));
    assume((b > 0));
    assume((x > 0));
    assume((y > 0));
    assume((r > 0));
    // Invariant using the GCD function.
    // precheck
    // loopcond : (b != a)

    if (choices > 105) {
      // pre-conditions
      x = a;
      y = b;
      // fprintf(fptr, "BEGIN : %d, %d, %d, %d, %d\n", a, b, x, y, r);
      assume((a > 0));
      assume((b > 0));
      assume((x > 0));
      assume((y > 0));
      assume((r > 0));
      if (fast_gcd) {
        shift = __builtin_ctz(a | b);
        a >>= __builtin_ctz(a);
      }
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, a, b, x, y, r);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(a, b, x, y, r));

      // Loop Condition
      if ((b != a)) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        // fprintf(fptr, "LOOP : %d, %d, %d, %d, %d\n", a, b, x, y, r);
        while ((b != a) && unroll--) {
          assume((loopflag == 0));
          unsigned int temp_a = a;
          unsigned int temp_b = b;
          unsigned int temp_x = x;
          unsigned int temp_y = y;
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
          loopcheck(fptr, vars, temp_a, temp_b, temp_x, temp_y, temp_r, a, b, x,
                    y, r);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if (fast_gcd) {
          r = a << shift;
        } else {
          r = a;
        }
        // fprintf(fptr, "POST : %d, %d, %d, %d, %d\n", a, b, x, y, r);
        postcount++;
        postcheck(fptr, vars, ((x % r == 0) && (y % r == 0)), a, b, x, y, r)
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