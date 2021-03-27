#include <75.h>
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

#define INV(c, x1, x2, x3, y, z) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int c, int x1, int x2, int x3, int y, int z)
{
  int f = preflag;
  aflcrash(INV(c, x1, x2, x3, y, z), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int c, int x1, int x2, int x3, int y, int z)
{
  int f = loopflag;
  aflcrash(INV(c, x1, x2, x3, y, z), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, c, x1, x2, x3, y, z)                     \
  \ 
{                                                             \
    \ 
    int f = postflag;                                            \
    \ 
   aflcrash(cond, postflag);                                     \
    \ 
    if (f == 0 && postflag == 1)                                 \
    {                                                            \
      \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "c",                                                            \
               c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z); \
      fflush(stderr);                                            \
    \ 
}                                                           \
  }

int main()
{
  // variable declarations
  int c;
  int x1;
  int x2;
  int x3;
  int y;
  int z;
  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    // pre-conditions
    y = buf[1];
    assume((y >= 0));
    assume((y >= 127));
    (c = 0);
    (z = (36 * y));
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      precheck(c, x1, x2, x3, y, z);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(c, x1, x2, x3, y, z));

      // Loop Condition
      if ((choices > 55))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((choices > 55) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            if ((c < 36))
            {
              (z = (z + 1));
              (c = (c + 1));
            }
          }
          loopcheck(c, x1, x2, x3, y, z);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c < 36))
          postcheck((z < 4608), c, x1, x2, x3, y, z)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}