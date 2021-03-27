#include <37.h>
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

#define INV(c) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int c)
{
  int f = preflag;
  aflcrash(INV(c), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d\n",
            "c", c);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int c)
{
  int f = loopflag;
  aflcrash(INV(c), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d\n",
            "c", c);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, c)       \
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
 "c",                            \
               c);               \
      fflush(stderr);            \
    \ 
}                           \
  }

int main()
{
  // variable declarations
  int c;
  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    c = buf[1];

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      precheck(c);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(c));

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
              if (unknown())
              {
                if ((c != 40))
                {
                  (c = (c + 1));
                }
              }
              else
              {
                if ((c == 40))
                {
                  (c = 1);
                }
              }
            }
          }
          loopcheck(c);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c < 0))
          if ((c > 40))
            postcheck((c == 40), c)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}