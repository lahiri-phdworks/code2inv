#include <101.h>
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

#define INV(n, x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int n, long long int x) {
  int f = preflag;
  aflcrash(INV(n, x), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "n", n, "x", x);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_n,
               long long int temp_x, long long int n, long long int x) {
  int f = loopflag;
  aflcrash(INV(n, x), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld\n", "n", temp_n, "x",
            temp_x);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld\n", "n", n, "x", x);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, n, x)                                      \
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
 "n",                                                                          \
                n, "x", x);                                                    \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int main() {
  // variable declarations
  long long int n;
  long long int x;

  char buff[2048];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 2048);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    assume(len > 6);
    long long int choices = buf[len - 1];
    n = buf[len - 2];
    x = buf[len - 4];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld\n", "n", n, "x", x);

    // pre-conditions
    assume((-10000 <= n && n <= 10000));
    // precheck
    // loopcond : (x < n)

    if (choices > 10000) {
      // pre-conditions
      assume((preflag == 0));
      (x = 0);
      precount++;
      precheck(fptr, vars, n, x);
    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, x));

      // Loop Condition
      if ((x < n)) {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < n) && k--) {
          assume((loopflag == 0));
          // loop body
          long long int temp_x = x;
          long long int temp_n = n;

          x = x + 1;

          loopcount++;
          loopcheck(fptr, vars, temp_n, temp_x, n, x);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((x != n)) {
          postcount++;
          postcheck(fptr, vars, (n < 0), n, x)
        }
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
  assert(0);
  return 0;
}