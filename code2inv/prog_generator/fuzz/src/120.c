#include <120.h>
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

#define INV(i, sn) PHI

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

FILE *file_descp;

// COMMENT : Precheck template
void precheck(char *buff, int i, int sn)
{
  int f = preflag;
  aflcrash(INV(i, sn), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "\nPre : %s\n",
            buff);
    // fflush(file_descp);
  }
}

// COMMENT : Loopcheck template
void loopcheck(char *buff, int i, int sn)
{
  int f = loopflag;
  aflcrash(INV(i, sn), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "\nLoop : %s\n",
            buff);
    // fflush(file_descp);
  }
}

// COMMENT : Postcheck template
#define postcheck(buff, cond, i, sn)                \
  \ 
{                                                \
    \ 
    int f = postflag;                               \
    \ 
   aflcrash(cond, postflag);                        \
    \ 
    if (f == 0 && postflag == 1)                    \
    {                                               \
      \ 
        fprintf(file_descp, "\nPost : %s\n", buff); \
    }                                               \
  }

int main()
{
  // variable declarations
  long long i;
  long long sn;

  FILE *fptr = fopen("models.txt", "w");
  file_descp = fptr;

  for (;;)
  {
    size_t len;
    const int32_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    i = buf[2];
    sn = buf[4];

    char vars[70] = "";
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 70, "%s : %lld, %s : %lld", "i", i, "sn", sn);

    // pre-conditions
    i = buf[1];
    sn = buf[2];
    // precheck
    // loopcond : (i <= 8)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (sn = 0);
      (i = 1);
      precheck(vars, i, sn);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, sn));

      // Loop Condition
      if ((i <= 8))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((i <= 8) && k--)
        {
          assume((loopflag == 0));
          {
            {
              (i = (i + 1));
              (sn = (sn + 1));
            }
          }
          loopcheck(vars, i, sn);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((sn != 8))
          postcheck(vars, (sn == 0), i, sn)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter >= 100)
    {
      fprintf(file_descp, "%s : %lld, %s : %lld, %s : %lld\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      fflush(file_descp);
      counter = 0;
    }

    fflush(file_descp);

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }

  return 0;
}