#include <141.h>
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

#define INV(i, n, out) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, int i, int n, int out) {
  int f = preflag;
  aflcrash(INV(i, n, out), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n,
            "out", out);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, int temp_i, int temp_n, int temp_out,
               int i, int n, int out) {
  int f = loopflag;
  aflcrash(INV(i, n, out), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i,
            "n", temp_n, "out", temp_out);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n,
            "out", out);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, n, out)                                 \
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
 "i",                                                                          \
                i, "n", n, "out", out);                                        \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int isprime(int n) {
  if (n <= 1)
    return 0;

  int flag = 1;
  for (auto i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      flag = 0;
      break;
    }
  }

  return flag;
}

int main() {
  // variable declarations
  int n;
  int i;
  int out;

  char buff[2048];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 2048);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    int choices = buf[0];
    n = buf[1];
    i = buf[2];
    out = buf[3];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n,
             "out", out);

    // pre-conditions
    // precheck
    // loopcond : (i < n)

    if (choices > 15000) {
      // pre-conditions
      assume((preflag == 0));
      assume((n > 2));
      (i = 0);
      (out = 0);
      precount++;
      precheck(fptr, vars, i, n, out);
    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, n, out));
      // Loop Condition
      if ((i < n)) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((i < n) && unroll--) {
          assume((loopflag == 0));
          int temp_n = n;
          int temp_i = i;
          int temp_out = out;
          {
            // loop body
            i = i + 1;
            if (isprime(n)) {
              out = out + 1;
            } else {
              out = out + 2;
            }
            // temp_n, temp_i, temp_out
          }
          // (n > 2) && (i <= n) && (isprime(n) && out = i || !isprime(n) && out
          // = 2 * i)
          loopcount++;
          loopcheck(fptr, vars, temp_n, temp_i, temp_out, i, n, out);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((i % 2 == 0) || (i == 5)) {
          postcount++;
          postcheck(fptr, vars,
                    ((i % 2 == 0) && (out == 2 * n)) ||
                        ((i == 5) && (out == 5)),
                    i, n, out)
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
  return 0;
}

/**
 * True : ((n > 2) && (i <= n) && (out == i))
 * False : ((n > 2) && (i <= n) && (out == (i * (i + 1)) / 2 ))
 * Complete Invariant : (n > 2) && (i <= n) && (isprime(n) && out == i ||
 * !isprime(n) && out == i*(i+1)/2)
 */