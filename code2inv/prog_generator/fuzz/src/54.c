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

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

FILE *file_descp;

// COMMENT : Precheck template
void precheck(char *buff, int c, int n, int v1, int v2, int v3)
{
  int f = preflag;
  aflcrash(INV(c, n, v1, v2, v3), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int c, int n, int v1, int v2, int v3)
{
  int f = loopflag;
  aflcrash(INV(c, n, v1, v2, v3), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, c, n, v1, v2, v3)   \
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
  int n;
  int v1;
  int v2;
  int v3;

  FILE *file_descp = fopen("models.txt", "w");
  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];

    char vars[100];
    snprintf(vars, 100, "%s : %d, %s : %d, %s : %d, %s : %d, %s : %d", "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);

    // pre-conditions
    assume((-10000 <= n && n <= 10000));
    c = buf[1];
    n = buf[2];
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      assume((n > 0));
      precheck(vars, c, n, v1, v2, v3);
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
          loopcheck(vars, c, n, v1, v2, v3);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c != n))
          postcheck(vars, (c <= n), c, n, v1, v2, v3)
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