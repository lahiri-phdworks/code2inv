#include <129.h>
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

#define INV(x, y) PHI

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

FILE *file_descp;

// COMMENT : Precheck template
void precheck(char *buff, int x, int y)
{
  int f = preflag;
  aflcrash(INV(x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, x, y)               \
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

int main()
{
  // variable declarations
  int x;
  int y;
  int z1;
  int z2;
  int z3;
  FILE *file_descp = fopen("models.txt", "w");
  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    char vars[100];
    snprintf(vars, 100, "%s : %d, %s : %d", "x", x, "y", y);

    // pre-conditions
    y = buf[1];
    x = buf[2];
    // precheck
    // loopcond : (x < y)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 1);
      precheck(vars, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y));

      // Loop Condition
      if ((x < y))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < y) && k--)
        {
          assume((loopflag == 0));
          {
            {
              (x = (x + x));
            }
          }
          loopcheck(vars, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck(vars, (x >= 1), x, y)
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