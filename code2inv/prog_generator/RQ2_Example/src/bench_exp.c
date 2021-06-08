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

#define INV(a, b) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int a, long long int b) {
  int f = preflag;
  aflcrash(INV(a, b), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "a", a, "b", b);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_a,
               long long int temp_b, long long int a, long long int b) {
  int f = loopflag;
  aflcrash(INV(a, b), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "a", temp_a, "b",
            temp_b);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "a", a, "b", b);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, a, b)                                      \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld\n", \ 
 "a",                                                                          \
                a, "b", b);                                                    \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int main() {
  // variable declarations
  int a;
  int b;
  int x;
  int y;
  long long res;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld\n", "a", a, "b", b);

    // pre-conditions
    a = buf[1];
    b = buf[2];
    res = buf[3];
    x = a;
    y = b;
    // precheck
    // loopcond : (b > 0)

    if (choices > 15000) {
      // pre-conditions
      a = 0;
      b = 0;
      x = a;
      y = b;
      res = 1;

      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, a, b);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(a, b));

      // Loop Condition
      if ((b > 0)) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((b > 0) && unroll--) {
          assume((loopflag == 0));
          int temp_a = a, temp_b = b;

          // loop body
          if (b & 1)
            res = res * a;
          a = a * a;
          b >>= 1;

          loopcount++;
          loopcheck(fptr, vars, temp_a, temp_b, a, b);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, ((a >= 0) && (b >= 0) && (res == pow(x, y))), a,
                  b)
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