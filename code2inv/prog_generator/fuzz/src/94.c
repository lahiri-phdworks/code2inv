#include <94.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 32

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(i, j, k, n) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int i, int j, int k, int n)
{
  int f = preflag;
  aflcrash(INV(i, j, k, n), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n",
            "i", i, "j", j, "k", k, "n", n);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int i, int j, int k, int n)
{
  int f = loopflag;
  aflcrash(INV(i, j, k, n), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n",
            "i", i, "j", j, "k", k, "n", n);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, i, j, k, n)        \
  \ 
{                                       \
    \ 
    int f = postflag;                      \
    \ 
   aflcrash(cond, postflag);               \
    \ 
    if (f == 0 && postflag == 1)           \
    {                                      \
      \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "i",                                      \
               i, "j", j, "k", k, "n", n); \
      fflush(stderr);                      \
    \ 
}                                     \
  }

int main()
{
  // variable declarations
  int i;
  int j;
  int k;
  int n;

  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    k = buf[1];
    n = buf[2];

    // pre-conditions
    assume((-10000 <= k && k <= 10000));
    assume((-10000 <= n && n <= 10000));

    // precheck
    // loopcond : (i <= n)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (i = 0);
      (j = 0);
      precheck(i, j, k, n);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j, k, n));

      // Loop Condition
      if ((i <= n))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((i <= n) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (i = (i + 1));
              (j = (j + i));
            }
          }
          loopcheck(i, j, k, n);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck(((i + (j + k)) > (2 * n)), i, j, k, n)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}