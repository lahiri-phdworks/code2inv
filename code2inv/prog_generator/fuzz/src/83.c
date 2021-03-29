#include <83.h>
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

#define INV(x, y) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(char *buff, int x, int y)
{
  int f = preflag;
  aflcrash(INV(x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s",
            buff);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s",
            buff);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, x, y) \
  \ 
{                                \
    \ 
    int f = postflag;               \
    \ 
   aflcrash(cond, postflag);        \
    \ 
    if (f == 0 && postflag == 1)    \
    {                               \
      \ 
       fprintf(stderr, "Post : %s",\ 
              buff);                \
      fflush(stderr);               \
    \ 
}                              \
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
    const int32_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    y = buf[1];
    x = buf[2];

    char vars[100];
    snprintf(vars, 100, "%s : %d, %s : %d\n", "x", x, "y", y);
    // pre-conditions
    // precheck
    // loopcond : (x < 0)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      precheck(vars, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      (x = -5000);
      assume(INV(x, y));

      // Loop Condition
      if ((x < 0))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < 0) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (x = (x + y));
              (y = (y + 1));
            }
          }
          loopcheck(vars, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck(vars, (y > 0), x, y)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}