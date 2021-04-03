#include <98.h>
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

    // pre-conditions
    y = buf[1];
    x = buf[2];
    i = buf[3];
    // precheck
    // loopcond : (i <= x)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (j = 0);
      (i = 0);
      (y = 2);
      precheck(i, j, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j, x, y));

      // Loop Condition
      if ((i <= x))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((i <= x) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (i = (i + 1));
              (j = (j + y));
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
        if ((i != j))
          postcheck((y != 1), i, j, x, y)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}