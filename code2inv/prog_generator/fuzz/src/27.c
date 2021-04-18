#include <27.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/file.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(n, x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int n, long long int x)
{
  int f = preflag;
  aflcrash(INV(n, x), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s : %lld, %s : %lld\n", "n", n, "x", x);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_n, long long int temp_x, long long int n, long long int x)
{
  int f = loopflag;
  aflcrash(INV(n, x), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld\n",
            "n", temp_n, "x", temp_x);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld\n",
            "n", n, "x", x);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, n, x)                               \
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
        fprintf(file_descp, "Post : %s : %lld, %s : %lld\n", "n", n, "x", x); \
      assert(0);                                                              \
    \ 
}                                                                        \
  }

int main()
{
  // variable declarations
  long long int n;
  long long int x;

  char buff[2048];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 2048);

  for (;;)
  {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    x = buf[2];
    n = buf[1];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld\n", "n", n, "x", x);

    // pre-conditions
    // precheck
    // loopcond : (x > 1)

    if (choices > 10000)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = n);
      precount++;
      precheck(fptr, vars, n, x);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, x));

      // Loop Condition
      if ((x > 1))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x > 1) && k--)
        {
          assume((loopflag == 0));
          long long int temp_x = x;
          long long int temp_n = n;
          // loop body
          {
            {
              (x = (x - 1));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, temp_n, temp_x, n, x);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if (n >= 0)
        {
          postcount++;
          postcheck(fptr, vars, (x == 1), n, x)
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