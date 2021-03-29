#include <89.h>
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

#define INV(lock, v1, v2, v3, x, y) PHI

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

FILE *file_descp;

// COMMENT : Precheck template
void precheck(char *buff, int lock, int v1, int v2, int v3, int x, int y)
{
  int f = preflag;
  aflcrash(INV(lock, v1, v2, v3, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int lock, int v1, int v2, int v3, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(lock, v1, v2, v3, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, lock, v1, v2, v3, x, y) \
  \ 
{                                                  \
    \ 
    int f = postflag;                                 \
    \ 
   aflcrash(cond, postflag);                          \
    \ 
    if (f == 0 && postflag == 1)                      \
    {                                                 \
      \ 
        fprintf(file_descp, "Post : %s\n", buff);     \
      \ 
fflush(file_descp);                                   \
    \ 
}                                                \
  }

int main()
{
  // variable declarations
  int lock;
  int v1;
  int v2;
  int v3;
  int x;
  int y;

  FILE *fptr = fopen("models.txt", "w");
  file_descp = fptr;
  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    y = buf[1];
    x = buf[2];
    lock = buf[3];

    char vars[100];
    snprintf(vars, 100, "%s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d",
             "lock", lock, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);

    // pre-conditions
    assume((-10000 <= y && y <= 10000));
    // precheck
    // loopcond : (x != y)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = y);
      (lock = 1);
      precheck(vars, lock, v1, v2, v3, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(lock, v1, v2, v3, x, y));

      // Loop Condition
      if ((x != y))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x != y) && k--)
        {
          assume((loopflag == 0));
          // loop body
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
          loopcheck(vars, lock, v1, v2, v3, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcheck(vars, (lock == 1), lock, v1, v2, v3, x, y)
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