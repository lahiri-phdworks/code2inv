#include <assert.h>
#include <bench_sqrt.h>
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

#define INV(n, left, right, mid) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int n, long long int left,
              long long int right, long long int mid) {
  int f = preflag;
  aflcrash(INV(n, left, right, mid), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "n", n,
            "left", left, "right", right, "mid", mid);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_n,
               long long int temp_left, long long int temp_right,
               long long int temp_mid, long long int n, long long int left,
               long long int right, long long int mid) {
  int f = loopflag;
  aflcrash(INV(n, left, right, mid), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", temp_n, "left", temp_left, "right", temp_right, "mid",
            temp_mid);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "n",
            n, "left", left, "right", right, "mid", mid);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, n, left, right, mid)                       \
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
 "n",                                                                          \
                n, "left", left, "right", right, "mid", mid);                  \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

double square_root(double x) {
  __asm__("fsqrt" : "+t"(x));
  return x;
}

int main() {
  // variable declarations
  int left;
  int right;
  int mid;
  unsigned int n;

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
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "n", n,
             "left", left, "right", right, "mid", mid);

    // pre-conditions
    n = buf[1];
    left = buff[2];
    right = n;
    // precheck
    // loopcond : (left <= right)

    if (choices > 100) {
      // pre-conditions
      n = 745;
      left = 0;
      right = n;
      assume((n >= 0));

      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, n, left, right, mid);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, left, right, mid));

      // Loop Condition
      if ((left <= right)) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((left <= right) && unroll--) {
          assume((loopflag == 0));
          int temp_n = n, temp_left = left, temp_right = right, temp_mid = mid;

          // loop body
          mid = (left + right) / 2;
          if (mid * mid <= n)
            left = mid + 1;
          else
            right = mid - 1;

          loopcount++;
          loopcheck(fptr, vars, temp_n, temp_left, temp_right, temp_mid, n,
                    left, right, mid);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, (round(square_root(n)) == left - 1), n, left,
                  right, mid)
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