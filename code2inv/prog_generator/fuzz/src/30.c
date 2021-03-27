#include <30.h>
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

#define INV(x) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int x)
{
  int f = preflag;
  aflcrash(INV(x), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d\n",
            "x", x);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int x)
{
  int f = loopflag;
  aflcrash(INV(x), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d\n",
            "x", x);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, x)       \
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
       fprintf(stderr, "Post : %s : %d\n",\ 
 "x",                            \
               x);               \
      fflush(stderr);            \
    \ 
}                           \
  }

int main()
{
  // variable declarations
  int x;

  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);
    x = buf[1];
    int choices = buf[0];

    // pre-conditions
    // precheck
    // loopcond : (x > 0)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 100);
      precheck(x);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x));

      // Loop Condition
      if ((x > 0))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x > 0) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (x = (x - 1));
            }
          }
          loopcheck(x);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck((x == 0), x)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}