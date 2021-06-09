#include <assert.h>
#include <bench_fibonacci.h>
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

#define INV(x, y, i, n) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int x, long long int y,
              long long int i, long long int n) {
  int f = preflag;
  aflcrash(INV(x, y, i, n), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x,
            "y", y, "i", i, "n", n);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_x,
               long long int temp_y, long long int temp_i, long long int temp_n,
               long long int x, long long int y, long long int i,
               long long int n) {
  int f = loopflag;
  aflcrash(INV(x, y, i, n), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "x", temp_x, "y", temp_y, "i", temp_i, "n", temp_n);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x",
            x, "y", y, "i", i, "n", n);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, x, y, i, n)                                \
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
 "x",                                                                          \
                x, "y", y, "i", i, "n", n);                                    \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

double fib(double n) {
  double phi = (1 + sqrt(5.0)) / 2;
  return round(pow(phi, n) / sqrt(5.0));
}

int main() {
  // variable declarations
  unsigned int x;
  unsigned int y;
  unsigned int i;
  double n;

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
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x,
             "y", y, "i", i, "n", (int)n);

    // pre-conditions
    x = buf[1];
    y = buf[2];
    n = buf[3];
    i = buf[4];
    // precheck
    // loopcond : (i < n)

    if (choices > 100) {
      // pre-conditions
      x = 0;
      y = 1;
      n = 10;
      i = 0;
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, x, y, i, (int)n);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y, i, (int)n));

      // Loop Condition
      if (i < n) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((i < n) && unroll--) {
          assume((loopflag == 0));
          int temp_x = x, temp_y = y, temp_i = i;
          double temp_n = n;

          // loop body
          // in-place output use in addition.
          asm("   movl    %2,%0;"
              "   addl    %1,%0;"
              : "=&r"(y)
              : "r"(x), "r"(y));
          x = y - x;
          i = i + 1;

          loopcount++;
          loopcheck(fptr, vars, temp_x, temp_y, temp_i, (int)temp_n, x, y, i,
                    (int)n);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars,
                  ((0 <= i) && (i <= n) && (n >= 0) && (x == (int)fib(i)) &&
                   (y == (int)fib(i + 1))),
                  x, y, i, (int)n)
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