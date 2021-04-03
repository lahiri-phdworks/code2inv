#include <121.h>
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

#define INV(i, sn) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int i, int sn)
{
  int f = preflag;
  aflcrash(INV(i, sn), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d\n",
            "i", i, "sn", sn);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int i, int sn)
{
  int f = loopflag;
  aflcrash(INV(i, sn), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d\n",
            "i", i, "sn", sn);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, i, sn)   \
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
 "i",                            \
               i, "sn", sn);     \
      fflush(stderr);            \
    \ 
}                           \
  }

int main()
{
  // variable declarations
  int i;
  int sn;

  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    i = buf[1];
    // pre-conditions
    assume((-10000 <= i && i <= 10000));
    // precheck
    // loopcond : (i <= 8)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (sn = 0);
      (i = 1);
      precheck(i, sn);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, sn));

      // Loop Condition
      if ((i <= 8))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((i <= 8) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (i = (i + 1));
              (sn = (sn + 1));
            }
          }
          loopcheck(i, sn);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((sn != 0))
          postcheck((sn == 8), i, sn)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}