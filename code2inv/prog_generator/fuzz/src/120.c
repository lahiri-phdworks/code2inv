#include <120.h>
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

#define INV(i, sn) PHI

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *p, char *buff, int i, int sn)
{
  int f = preflag;
  aflcrash(INV(i, sn), preflag);
  if (f == 0 && preflag == 1)
  {
    flock(fileno(p), LOCK_SH);
    fprintf(p, "\nPre : %s\n",
            buff);
    flock(fileno(p), LOCK_UN);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *p, char *buff, int i, int sn)
{
  int f = loopflag;
  aflcrash(INV(i, sn), loopflag);
  if (f == 0 && loopflag == 1)
  {
    flock(fileno(p), LOCK_SH);
    fprintf(p, "\nLoop : %s\n",
            buff);
    flock(fileno(p), LOCK_UN);
  }
}

// COMMENT : Postcheck template
#define postcheck(p, buff, cond, i, sn)  \
  \ 
{                                     \
    \ 
    int f = postflag;                    \
    \ 
   aflcrash(cond, postflag);             \
    \ 
    if (f == 0 && postflag == 1)         \
    {                                    \
      \ 
      flock(fileno(p), LOCK_SH);         \
      fprintf(p, "\nPost : %s\n", buff); \
      flock(fileno(p), LOCK_UN);         \
    }                                    \
  }

int main()
{
  // variable declarations
  long long int i;
  long long int sn;

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
    i = buf[2];
    sn = buf[4];

    char vars[75];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 75, "%s : %lld, %s : %lld", "i", i, "sn", sn);

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
      precheck(fptr, vars, i, sn);
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
          loopcheck(fptr, vars, i, sn);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((sn != 8))
          postcheck(fptr, vars, (sn == 0), i, sn)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter >= 100)
    {
      fprintf(fptr, "\n%s : %lld, %s : %lld, %s : %lld\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }

  return 0;
}