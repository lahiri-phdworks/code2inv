#include <assert.h>
#include <bench_exp.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
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

#define INV(res, a, b, x, y) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int res, long long int a,
              long long int b, double x, double y) {
  int f = preflag;
  aflcrash(INV(res, a, b, x, y), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %d, %s : %d\n",
            "res", res, "a", a, "b", b, "x", (int)x, "y", (int)y);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_res,
               long long int temp_a, long long int temp_b, double temp_x,
               double temp_y, long long int res, long long int a,
               long long int b, double x, double y) {
  int f = loopflag;
  aflcrash(INV(res, a, b, x, y), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr,
            "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %d, %s : %d\n",
            "res", temp_res, "a", temp_a, "b", temp_b, "x", (int)temp_x, "y",
            (int)temp_y);
    fprintf(fptr,
            "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %d, %s : %d\n",
            "res", res, "a", a, "b", b, "x", (int)x, "y", (int)y);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, res, a, b, x, y)                           \
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
          fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %d, %s : %d\n", \ 
 "res",                                                                        \
          res, "a", a, "b", b, "x", (int)x, "y", (int)y);                      \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

// (a >= 0) && (b >= 0) && (res * pow (a, b) == pow (x, y))

int main() {
  // variable declarations
  unsigned long long int a;
  unsigned long long int b;
  double x;
  double y;
  unsigned long long int res;

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
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %d, %s : %d\n",
             "res", res, "a", a, "b", b, "x", (int)x, "y", (int)y);

    // restricted since the range is huge
    // and the computation otherwise would
    // overflow.
    a = buf[1] % 13 + 1;
    b = buf[2] % 13;
    res = 1LL;
    x = a;
    y = b;

    // precheck
    // loopcond : (b > 0)

    if (choices > 100) {
      // pre-conditions
      a = 5;
      b = 3;
      x = a;
      y = b;
      res = 1LL;

      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, res, a, b, x, y);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(res, a, b, x, y));

      // Loop Condition
      if (b > 0) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((b > 0) && unroll--) {
          assume((loopflag == 0));
          int temp_a = a, temp_b = b, temp_res = res;

          // loop body
          // exponentiation by squaring
          if (b & 1)
            res *= a;
          b >>= 1;
          a *= a;

          loopcount++;
          loopcheck(fptr, vars, temp_res, temp_a, temp_b, x, y, res, a, b, x,
                    y);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        // fprintf(fptr, "%d, %d, %d, %d\n", res, (int)pow(x, y), a, b);
        postcheck(fptr, vars, ((a >= 0) && (b >= 0) && (res == (int)pow(x, y))),
                  res, a, b, x, y)
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