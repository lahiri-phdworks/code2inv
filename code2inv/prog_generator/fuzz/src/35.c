#include <35.h>
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

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

FILE *file_descp;

// COMMENT : Precheck template
void precheck(char *buff, int c)
{
  int f = preflag;
  aflcrash(INV(c), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int c)
{
  int f = loopflag;
  aflcrash(INV(c), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, c)                  \
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
  int c;

  FILE *fptr = fopen("models.txt", "w");
  file_descp = fptr;
  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    c = buf[1];

    char vars[100];
    snprintf(vars, 100, "%s : %d", "c", c);

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      precheck(vars, c);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(c));

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
          loopcheck(vars, c);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c != 40))
          postcheck(vars, (c >= 0), c)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(file_descp, "%s : %d, %s : %d, %s : %d\n", "precount", precount, "loopcount", loopcount, "postcount", postcount);
      fflush(file_descp);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}