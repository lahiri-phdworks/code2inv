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

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

FILE *file_descp;

// COMMENT : Precheck template
void precheck(char *buff, int i, int j, int x, int y)
{
  int f = preflag;
  aflcrash(INV(i, j, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int i, int j, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(i, j, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, i, j, x, y)         \
  \ 
{                                              \
    \ 
    int f = postflag;                             \
    \ 
   aflcrash(cond, postflag);                      \
    \ 
    if (f == 0 && postflag == 1)                  \
    {                                             \
      \ 
        fprintf(file_descp, "Post : %s\n", buff); \
      \ 
fflush(file_descp);                               \
    \ 
}                                            \
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

  FILE *file_descp = fopen("models.txt", "w");
  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    i = buf[1];
    y = buf[2];

    char vars[100];
    snprintf(vars, 100, "%s : %d, %s : %d, %s : %d, %s : %d", "i", i, "j", j, "x", x, "y", y);

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
          loopcheck(vars, i, j, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((y == 1))
          postcheck(vars, (i == j), i, j, x, y)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(file_descp, "%s : %d, %s : %d, %s : %d\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      fflush(file_descp);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}