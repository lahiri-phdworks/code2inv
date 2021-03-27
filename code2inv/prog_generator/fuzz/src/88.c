#include <88.h>
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

#define INV(lock, x, y) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int lock, int x, int y)
{
  int f = preflag;
  aflcrash(INV(lock, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n",
            "lock", lock, "x", x, "y", y);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int lock, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(lock, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n",
            "lock", lock, "x", x, "y", y);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, lock, x, y)   \
  \ 
{                                  \
    \ 
    int f = postflag;                 \
    \ 
   aflcrash(cond, postflag);          \
    \ 
    if (f == 0 && postflag == 1)      \
    {                                 \
      \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n",\ 
 "lock",                              \
               lock, "x", x, "y", y); \
      fflush(stderr);                 \
    \ 
}                                \
  }

int main()
{
  // variable declarations
  int lock;
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
    x = buf[1];
    (y = (x + 1));
    (lock = 0);
    // precheck
    // loopcond : (x != y)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      precheck(lock, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(lock, x, y));

      // Loop Condition
      if ((x != y))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x != y) && k--)
        {
          assume((loopflag == 0));
          {
            {
              if (choices > 63)
              {
                {
                  (lock = 1);
                  (x = y);
                }
              }
              else
              {
                {
                  (lock = 0);
                  (x = y);
                  (y = (y + 1));
                }
              }
            }
          }
          loopcheck(lock, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck((lock == 1), lock, x, y)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}