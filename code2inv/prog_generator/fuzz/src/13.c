#include <13.h>
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
void precheck(int x, int y)
{
  int f = preflag;
  aflcrash(INV(x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stdout, "Pre : %s : %d, %s : %d\n",
            "x", x, "y", y);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int x, int y)
{
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stdout, "Loop : %s : %d, %s : %d\n",
            "x", x, "y", y);
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
       fprintf(stdout, "Post : %s : %d, %s : %d\n",\ 
 "x",                            \
               x, "y", y);       \
    \ 
}                           \
  }

int main()
{
  // variable declarations
  int x;
  int y;
  int z1;
  int z2;
  int z3;
  freopen("models.txt", "w", stdout);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    // pre-conditions
    x = buf[1];
    y = buf[2];
    // precheck
    // loopcond : unknown()

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      assume((x >= 0));
      assume((x <= 2));
      assume((y <= 2));
      assume((y >= 0));
      precheck(x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y));

      // Loop Condition
      if ((choices > 50))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((choices > 50) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (x = (x + 2));
              (y = (y + 2));
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
        if ((x == 4))
          postcheck((y != 0), x, y)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}