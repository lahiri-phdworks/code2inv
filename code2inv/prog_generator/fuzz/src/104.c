#include <104.h>
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

#define INV(n, v1, v2, v3, x) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int n, int v1, int v2, int v3, int x)
{
  int f = preflag;
  aflcrash(INV(n, v1, v2, v3, x), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(int n, int v1, int v2, int v3, int x)
{
  int f = loopflag;
  aflcrash(INV(n, v1, v2, v3, x), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
            "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(cond, n, v1, v2, v3, x)                \
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
 "n",                                                    \
               n, "v1", v1, "v2", v2, "v3", v3, "x", x); \
      fflush(stderr);                                    \
    \ 
}                                                   \
  }

int main()
{
  // variable declarations
  int n;
  int v1;
  int v2;
  int v3;
  int x;
  freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    // pre-conditions
    n = buf[1];
    x = buf[2];
    // precheck
    // loopcond : (x < n)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 0);
      precheck(n, v1, v2, v3, x);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, v1, v2, v3, x));

      // Loop Condition
      if ((x < n))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < n) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (x = (x + 1));
            }
          }
          loopcheck(n, v1, v2, v3, x);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((x != n))
          postcheck((n < 0), n, v1, v2, v3, x)
      }
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}