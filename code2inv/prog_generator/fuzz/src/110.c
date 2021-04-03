#include <110.h>
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

#define INV(i, n, sn) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int i, int n, int sn)
{
  int f = preflag;
  aflcrash(INV(i, n, sn), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n",
            "i", i, "n", n, "sn", sn);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int i, int n, int sn)
{
  int f = loopflag;
  aflcrash(INV(i, n, sn), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n",
            "i", i, "n", n, "sn", sn);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, i, n, sn)    \
  \ 
{                                 \
    \ 
    int f = postflag;                \
    \ 
   aflcrash(cond, postflag);         \
    \ 
    if (f == 0 && postflag == 1)     \
    {                                \
      \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n",\ 
 "i",                                \
               i, "n", n, "sn", sn); \
      fflush(stderr);                \
    \ 
}                               \
  }

int main()
{
  // variable declarations
  int i;
  int n;
  int sn;
  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    // pre-conditions
    n = buf[1];
    sn = buf[2];
    // precheck
    // loopcond : (i <= n)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (sn = 0);
      (i = 1);
      precheck(i, n, sn);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, n, sn));

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
              (sn = (sn + 1));
            }
          }
          loopcheck(i, n, sn);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((sn != n))
          postcheck((sn == 0), i, n, sn)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}