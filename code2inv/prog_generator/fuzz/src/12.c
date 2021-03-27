#include <12.h>
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

#define INV(x, y, z1, z2, z3) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int x, int y, int z1, int z2, int z3)
{
  int f = preflag;
  aflcrash(INV(x, y, z1, z2, z3), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int x, int y, int z1, int z2, int z3)
{
  int f = loopflag;
  aflcrash(INV(x, y, z1, z2, z3), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, x, y, z1, z2, z3)                \
  \ 
{                                                     \
    \ 
    int f = postflag;                                    \
    \ 
   aflcrash(cond, postflag);                             \
    \ 
    if (f == 0 && postflag == 1)                         \
    {                                                    \
      \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "x",                                                    \
               x, "y", y, "z1", z1, "z2", z2, "z3", z3); \
      fflush(stderr);                                    \
    \ 
}                                                   \
  }

int main()
{
  // variable declarations
  int x;
  int y;
  int z1;
  int z2;
  int z3;
  freopen("models.txt", "w", stderr);

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
      assume((x <= 10));
      assume((y <= 10));
      assume((y >= 0));
      precheck(x, y, z1, z2, z3);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y, z1, z2, z3));

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
            {
              (x = (x + 10));
              (y = (y + 10));
            }
          }
          loopcheck(x, y, z1, z2, z3);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((y == 0))
          postcheck((x != 20), x, y, z1, z2, z3)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}