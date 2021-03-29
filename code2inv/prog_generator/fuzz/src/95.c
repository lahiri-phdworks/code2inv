#include <95.h>
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

#define INV(i, j, x, y) PHI

int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

int counter;

// COMMENT : Precheck template
void precheck(char *buff, int i, int j, int x, int y)
{
  int f = preflag;
  aflcrash(INV(i, j, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(stderr, "Pre : %s", buff);
    fflush(stderr);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int i, int j, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(i, j, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(stderr, "Loop : %s", buff);
    fflush(stderr);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, i, j, x, y)  \
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
       fprintf(stderr, "Post : %s", buff); \
      fflush(stderr);                      \
    \ 
}                                     \
  }

int incr1(int a, int b)
{
  return b + a;
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
    counter;
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    i = buf[1];
    x = buf[3];
    j = buf[4];
    y = buf[2];

    char vars[100];
    snprintf(vars, 100, "%s : %d, %s : %d, %s : %d, %s : %d\n",
             "i", i, "j", j, "x", x, "y", y);

    // pre-conditions
    // precheck
    // loopcond : (i <= x)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (j = 0);
      (i = 0);
      (y = 1);
      precount++;
      precheck(vars, i, j, x, y);
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
              (i = incr1(i, 1));
              (j = (j + y));
            }
          }
          loopcount++;
          loopcheck(vars, i, j, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((y == 1))
        {
          postcount++;
          postcheck(vars, (i == j), i, j, x, y)
        }
      }
    }

    if (preflag + loopflag + postflag == 0 && counter >= 100)
    {
      // print
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}