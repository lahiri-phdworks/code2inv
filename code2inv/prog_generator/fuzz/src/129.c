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

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, int x, int y)
{
  int f = preflag;
  aflcrash(INV(x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "\nPre : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "\nLoop : %s\n",
            buff);
    fflush(file_descp);
  }
}

// COMMENT : Postcheck template
#define postcheck(p, buff, cond, x, y)     \
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
        fprintf(p, "\nPost : %s\n", buff); \
    }                                      \
  }

int main()
{
  // variable declarations
  int x;
  int y;
  int z1;
  int z2;
  int z3;

  char buff[500];
  memset(buff, '\0', sizeof(buff));
  FILE *fptr = fopen("models.txt", "w");

  // COMMENT : This must be line buffered.
  setvbuf(fptr, buff, _IOLBF, 500);

  for (;;)
  {
    size_t len;
    const int32_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    y = buf[2];
    x = buf[4];

    char vars[75];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 75, "%s : %lld, %s : %lld\n", "x", x, "y", y);

    // pre-conditions
    // precheck
    // loopcond : (x < y)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 1);
      precount++;
      precheck(fptr, vars, x, y);
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
          loopcount++;
          loopcheck(fptr, vars, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, (x >= 1), x, y)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(fptr, "\n%s : %lld, %s : %lld, %s : %lld\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      // fflush(fptr);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}