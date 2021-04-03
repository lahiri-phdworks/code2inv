#include <128.h>
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

#define INV(x, y) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int x, int y)
{
  int f = preflag;
  aflcrash(INV(x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d\n",
            "x", x, "y", y);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int x, int y)
{
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d\n",
            "x", x, "y", y);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, x, y)    \
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
 "x",                            \
               x, "y", y);       \
      fflush(stderr);            \
    \ 
}                           \
  }

int main()
{
  // variable declarations
  int x;
  int y;
  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    // pre-conditions
    y = buf[1];
    x = buf[2];
    // precheck
    // loopcond : (x < y)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 1);
      precheck(x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y));

      // Loop Condition
      if ((x < y))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < y) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (x = (x + x));
            }
          }
          loopcheck(x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck((x >= 1), x, y)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}