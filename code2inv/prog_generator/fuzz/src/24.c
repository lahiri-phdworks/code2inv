#include <24.h>
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

#define INV(i, j) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int i, int j)
{
  int f = preflag;
  aflcrash(INV(i, j), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d\n",
            "i", i, "j", j);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int i, int j)
{
  int f = loopflag;
  aflcrash(INV(i, j), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d\n",
            "i", i, "j", j);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, i, j)    \
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
               i, "j", j);       \
      fflush(stderr);            \
    \ 
}                           \
  }

int main()
{
  // variable declarations
  int i;
  int j;
  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    i = buf[1];
    int choices = buf[0];

    // pre-conditions
    // precheck
    // loopcond : (j >= i)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (i = 1);
      (j = 10);
      precheck(i, j);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j));

      // Loop Condition
      if ((j >= i))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((j >= i) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (i = (i + 2));
              (j = (j - 1));
            }
          }
          loopcheck(i, j);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck((j == 6), i, j)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}