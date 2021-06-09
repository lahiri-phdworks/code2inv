#include <assert.h>
#include <bench_intdiv_simple.h>
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

#define INV(r, q, d) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int r, long long int q,
              long long int d) {
  int f = preflag;
  aflcrash(INV(r, q, d), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "r", r, "q", q,
            "d", d);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_r,
               long long int temp_q, long long int temp_d, long long int r,
               long long int q, long long int d) {
  int f = loopflag;
  aflcrash(INV(r, q, d), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "r", temp_r,
            "q", temp_q, "d", temp_d);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "r", r, "q", q,
            "d", d);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, r, q, d)                                   \
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
 "r",                                                                          \
                r, "q", q, "d", d);                                            \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int remainder(int a, int d) {
  int quo, rem;
  __asm__("movl $0x0, %%edx;"
          "movl %2, %%eax;"
          "movl %3, %%ebx;"
          "idivl %%ebx;"
          : "=a"(quo), "=d"(rem)
          : "g"(a), "g"(d));
  return rem;
}

int main() {
  // variable declarations
  int q;
  int r;
  int a;
  int d;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const uint16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n", "r", r, "q", q,
             "d", d);

    // pre-conditions
    a = buf[1];
    d = buf[2];
    r = a;
    q = 0;
    // precheck
    // loopcond : (r >= d)

    if (choices > 15000) {
      // pre-conditions
      a = 7454;
      d = 13;
      r = a;
      q = 0;
      assume((a >= 0));
      assume((d > 0));
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, r, q, d);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(r, q, d));

      // Loop Condition
      if ((r >= d)) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((r >= d) && unroll--) {
          assume((loopflag == 0));
          int temp_r = r, temp_q = q, temp_d = d;

          // loop body
          q = q + 1;
          r = r - d;

          loopcount++;
          loopcheck(fptr, vars, temp_r, temp_q, temp_d, r, q, d);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, ((0 <= r <= d) && (a / d == q)), r, q, d)
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