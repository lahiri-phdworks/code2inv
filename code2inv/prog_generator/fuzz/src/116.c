#include <116.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 10

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(sn, x) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int sn, int x)
{
  int f = preflag;
  aflcrash(INV(sn, x), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d\n",
            "sn", sn, "x", x);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int sn, int x)
{
  int f = loopflag;
  aflcrash(INV(sn, x), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d\n",
            "sn", sn, "x", x);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, sn, x)   \
  \ 
{                             \
    \ 
    int f = postflag;            \
    \ 
   aflcrash(cond, postflag);     \
    \ 
    if (f == 0 && postflag == 1) \
    {                            \
      \ 
       fprintf(stderr, "Post : %s : %d, %s : %d\n",\ 
 "sn",                           \
               sn, "x", x);      \
      fflush(stderr);            \
    \ 
}                           \
  }

int main()
{
  // variable declarations
  int sn;
  int v1;
  int v2;
  int v3;
  int x;
  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    // pre-conditions
    sn = buf[2];
    x = buf[3];
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (sn = 0);
      (x = 0);
      precheck(sn, x);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(sn, x));

      // Loop Condition
      if ((unknown()))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((unknown()) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (x = (x + 1));
              (sn = (sn + 1));
            }
          }
          loopcheck(sn, x);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((sn != x))
          postcheck((sn == -1), sn, x)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}