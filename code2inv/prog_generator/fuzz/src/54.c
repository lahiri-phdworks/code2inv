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

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, int c, int n, int v1, int v2, int v3)
{
  int f = preflag;
  aflcrash(INV(c, n, v1, v2, v3), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "\nPre : %s\n",
            buff);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, int c, int n, int v1, int v2, int v3)
{
  int f = loopflag;
  aflcrash(INV(c, n, v1, v2, v3), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "\nLoop : %s\n",
            buff);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, c, n, v1, v2, v3) \
  \ 
{                                                        \
    \ 
    int f = postflag;                                       \
    \ 
   aflcrash(cond, postflag);                                \
    \ 
    if (f == 0 && postflag == 1)                            \
    {                                                       \
      \ 
        fprintf(file_descp, "\nPost : %s\n", buff);         \
    }                                                       \
  }

int main()
{
  // variable declarations
  int c;
  int n;
  int v1;
  int v2;
  int v3;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));
  FILE *fptr = fopen("models.txt", "w");

  // COMMENT : This must be line buffered.
  setvbuf(fptr, buff, _IOLBF, 1024);

  for (;;)
  {
    size_t len;
    const int32_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    c = buf[1];
    n = buf[2];

    char vars[150];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 150, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld",
             "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);

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
      precount++;
      precheck(fptr, vars, c, n, v1, v2, v3);
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
          loopcount++;
          loopcheck(fptr, vars, c, n, v1, v2, v3);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c != n))
        {
          postcount++;
          postcheck(fptr, vars, (c <= n), c, n, v1, v2, v3)
        }
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(fptr, "\n%s : %lld, %s : %lld, %s : %lld\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}