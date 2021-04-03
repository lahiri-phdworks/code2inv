#include <24.h>
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

#define INV(i, j) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int i, long long int j)
{
  int f = preflag;
  aflcrash(INV(i, j), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int i, long long int j)
{
  int f = loopflag;
  aflcrash(INV(i, j), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, i, j)      \
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
  long long int i;
  long long int j;

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
    i = buf[1];
    j = buf[2];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld", "i", i, "j", j);

    // pre-conditions
    // precheck
    // loopcond : (j >= i)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (i = 1);
      (j = 10);
      precount++;
      precheck(fptr, vars, i, j);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j));

      // Loop Condition
      if ((j >= i))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((j >= i) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              (i = (i + 2));
              (j = (j - 1));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, i, j);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        {
          postcount++;
          postcheck(fptr, vars, (j == 6), i, j)
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