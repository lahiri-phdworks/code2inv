#include <83.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 128

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
    fprintf(file_descp, "Pre : %s : %lld, %s : %lld\n", "x", x, "y", y);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_x,
               long long int temp_y, long long int x, long long int y)
{
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld\n",
            "x", temp_x, "y", temp_y);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld\n",
            "x", x, "y", y);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, y)                               \
  \ 
{                                                                          \
    \ 
    int f = postflag;                                                         \
    \ 
   aflcrash(cond, postflag);                                                  \
    \ 
    if (f == 0 && postflag == 1)                                              \
    {                                                                         \
      \ 
        fprintf(file_descp, "Post : %s : %lld, %s : %lld\n", "x", x, "y", y); \
      assert(0);                                                              \
    }                                                                         \
  }

int main()
{
  // variable declarations
  long long int x;
  long long int y;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));
  FILE *fptr = fopen("models.txt", "w");

  // COMMENT : This must be line buffered.
  setvbuf(fptr, buff, _IOLBF, 1024);

  for (;;)
  {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    int choices = buf[0];
    y = buf[1];
    x = buf[2];

    char vars[50];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 50, "%s : %lld, %s : %lld\n", "x", x, "y", y);

    // pre-conditions
    // precheck
    // loopcond : (x < 0)

    if (choices > 10000)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = -5000);
      precount++;
      precheck(fptr, vars, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y));

      // Loop Condition
      if ((x < 0))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < 0) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_x = x;
          long long int temp_y = y;
          {
            {
              (x = (x + y));
              (y = (y + 1));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, temp_x, temp_y, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, (y > 0), x, y)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(fptr, "\n%s : %lld, %s : %lld, %s : %lld\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      // fflush(file_descp);
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