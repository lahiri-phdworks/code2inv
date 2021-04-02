#include <95.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/file.h>
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

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, int i, int j, int x, int y)
{
  int f = preflag;
  aflcrash(INV(i, j, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "\nPre : %s\n",
            buff);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, int i, int j, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(i, j, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "\nLoop : %s\n",
            buff);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, i, j, x, y) \
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
      fprintf(fptr, "\nPost : %s\n", buff);           \
    }                                                 \
  }

// COMMENT : External Function Call
// Z3 will fail in this case
int func(int a, int b)
{
  return b + a;
}

int main()
{
  // variable declarations
  long long int i;
  long long int j;
  long long int x;
  long long int y;

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

    int choices = buf[1];
    i = buf[2];
    y = buf[4];
    j = buf[5];
    x = buf[3];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld",
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
      precheck(fptr, vars, i, j, x, y);
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
              (i = func(i, 1));
              (j = (j + y));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, i, j, x, y);
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
          postcheck(fptr, vars, (i == j), i, j, x, y)
        }
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
    {
      fclose(fptr);
      assert(0);
    }
  }

  fclose(fptr);
  return 0;
}