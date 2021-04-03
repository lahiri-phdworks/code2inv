#include <124.h>
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

#define INV(i, j, x, y) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int i, int j, int x, int y)
{
  int f = preflag;
  aflcrash(INV(i, j, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n",
            "i", i, "j", j, "x", x, "y", y);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int i, int j, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(i, j, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n",
            "i", i, "j", j, "x", x, "y", y);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, i, j, x, y)        \
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
               i, "j", j, "x", x, "y", y); \
      fflush(stderr);                      \
    \ 
}                                     \
  }

int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;

  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    x = buf[1];
    y = buf[2];

    // pre-conditions
    assume((-10000 <= y && y <= 10000));
    assume((-10000 <= x && x <= 10000));
    // precheck
    // loopcond : (x != 0)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (i = x);
      (j = y);
      precheck(i, j, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j, x, y));

      // Loop Condition
      if ((x != 0))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x != 0) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (x = (x - 1));
              (y = (y - 1));
            }
          }
          loopcheck(i, j, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((i == j))
          postcheck((y == 0), i, j, x, y)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}