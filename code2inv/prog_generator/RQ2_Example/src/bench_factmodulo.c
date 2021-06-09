#include <assert.h>
#include <bench_factmodulo.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 32
#define PRIME 100003
static int f[PRIME];

int factmod(int n, int p) {
  if (n >= p)
    return 0;
  int res = 1;
  while (n > 1) {
    if ((n / p) % 2)
      res = p - res;
    res = res * f[n % p] % p;
    n /= p;
  }
  return res;
}

#define aflcrash(cond, flag)                                                   \
  if (!cond)                                                                   \
    flag = 1;

#define assume(cond)                                                           \
  if (!cond)                                                                   \
    continue;

#define INV(n, k, r, p) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int n, long long int k,
              long long int r, long long int p) {
  int f = preflag;
  aflcrash(INV(n, k, r, p), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "n", n,
            "k", k, "r", r, "p", p);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_n,
               long long int temp_k, long long int temp_r, long long int temp_p,
               long long int n, long long int k, long long int r,
               long long int p) {
  int f = loopflag;
  aflcrash(INV(n, k, r, p), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", temp_n, "k", temp_k, "r", temp_r, "p", temp_p);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "n",
            n, "k", k, "r", r, "p", p);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, n, k, r, p)                                \
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
                n, "k", k, "r", r, "p", p);                                    \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int main() {
  // variable declarations
  int n;
  int p;
  long long int r;
  int k;

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
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "n", n,
             "k", k, "r", r, "p", p);

    // pre-conditions
    n = buf[1];
    p = PRIME;

    f[0] = 1;
    for (int i = 1; i < p; i++)
      f[i] = f[i - 1] * i % p;
    // precheck
    // loopcond : (k != n)

    if (choices > 15000) {
      // pre-conditions
      r = 1;
      k = 0;
      n = 10;
      p = PRIME;

      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, n, k, r, p);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, k, r, p));

      // Loop Condition
      if (k != n) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((k != n) && unroll--) {
          assume((loopflag == 0));
          int temp_n = n, temp_k = k, temp_r = r, temp_p = p;

          // loopbody
          k = k + 1;
          r = (r * k) % PRIME;

          loopcount++;
          loopcheck(fptr, vars, temp_n, temp_k, temp_r, temp_p, n, k, r, p);
        }

      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars,
                  ((n >= 0) && (k >= 0) && (r == factmod(n, PRIME))), n, k, r,
                  p)
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