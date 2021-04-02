#include <26.h>
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

#define INV(n, x) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int n, long long int x)
{
  int f = preflag;
  aflcrash(INV(n, x), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int n, long long int x)
{
  int f = loopflag;
  aflcrash(INV(n, x), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, n, x)      \
  \ 
{                                                 \
    \ 
    int f = postflag;                                \
    \ 
   aflcrash(cond, postflag);                         \
    \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(file_descp, "Post : %s\n", buff); \ 
} \
  }

int main()
{
  // variable declarations
  long long int n;
  long long int x;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  for (;;)
  {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);

    long long int choices = buf[0];
    n = buf[1];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld", "n", n, "x", x);

    // pre-conditions
    assume((-10000 <= n && n <= 10000));
    // precheck
    // loopcond : (x > 1)

    if (choices > 25)
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
          // loop body
          {
            {
              (x = (x - 1));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, n, x);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((x != 1))
        {
          postcount++;
          postcheck(fptr, vars, (n < 0), n, x)
        }
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount", loopcount, "postcount", postcount);
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