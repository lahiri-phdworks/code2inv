#include <116.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/file.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 32

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(sn, x) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int sn, long long int x)
{
  int f = preflag;
  aflcrash(INV(sn, x), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s : %lld, %s : %lld\n", "sn", sn, "x", x);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_sn,
               long long int temp_x, long long int sn, long long int x)
{
  int f = loopflag;
  aflcrash(INV(sn, x), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld\n",
            "sn", temp_sn, "x", temp_x);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld\n",
            "sn", sn, "x", x);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, sn, x)                                   \
  \ 
{                                                                               \
    \ 
    int f = postflag;                                                              \
    \ 
   aflcrash(cond, postflag);                                                       \
    \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(file_descp, "Post : %s : %lld, %s : %lld\n", "sn", sn, "x", x); \ 
} \
  }

int main()
{
  // variable declarations
  long long int sn;
  long long int v1;
  long long int v2;
  long long int v3;
  long long int x;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  for (;;)
  {
    size_t len;
    const int8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    sn = buf[2];
    x = buf[3];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld\n", "sn", sn, "x", x);

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (sn = 0);
      (x = 0);
      precount++;
      precheck(fptr, vars, sn, x);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(sn, x));

      // Loop Condition
      if ((choices > 55))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((choices > 55) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_x = x;
          long long int temp_sn = sn;
          {
            {
              (x = (x + 1));
              (sn = (sn + 1));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, temp_sn, temp_x, sn, x);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((sn != x))
        {
          postcount++;
          postcheck(fptr, vars, (sn == -1), sn, x)
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