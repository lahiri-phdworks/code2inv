#include <54.h>
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

#define INV(c, n, v1, v2, v3) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int c, int n, int v1, int v2, int v3)
{
  int f = preflag;
  aflcrash(INV(c, n, v1, v2, v3), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int c, int n, int v1, int v2, int v3)
{
  int f = loopflag;
  aflcrash(INV(c, n, v1, v2, v3), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, c, n, v1, v2, v3)                \
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
 "c",                                                    \
               c, "n", n, "v1", v1, "v2", v2, "v3", v3); \
      fflush(stderr);                                    \
    \ 
}                                                   \
  }

int main()
{
  // variable declarations
  int c;
  int n;
  int v1;
  int v2;
  int v3;

  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    c = buf[1];
    n = buf[2];
    // pre-conditions
    assume((-10000 <= n && n <= 10000));
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      assume((n > 0));
      precheck(c, n, v1, v2, v3);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(c, n, v1, v2, v3));

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
              if (choices > 63)
              {
                if ((c > n))
                {
                  (c = (c + 1));
                }
              }
              else
              {
                if ((c == n))
                {
                  (c = 1);
                }
              }
            }
          }
          loopcheck(c, n, v1, v2, v3);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c != n))
          postcheck((c <= n), c, n, v1, v2, v3)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}