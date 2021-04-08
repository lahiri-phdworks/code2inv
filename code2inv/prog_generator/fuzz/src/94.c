#include <94.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 100

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(i, j, k, n) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int i, long long int j, long long int k, long long int n)
{
  int f = preflag;
  aflcrash(INV(i, j, k, n), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "j", j, "k", k, "n", n);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_i, long long int temp_j, long long int i, long long int j, long long int k, long long int n)
{
  int f = loopflag;
  aflcrash(INV(i, j, k, n), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", temp_i, "j", temp_j, "k", k, "n", n);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "j", j, "k", k, "n", n);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, j, k, n) \
  \ 
{                                            \
    \ 
    int f = postflag;                           \
    \ 
   aflcrash(cond, postflag);                    \
    \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                           \
                i, "j", j, "k", k, "n", n); \ 
}  \
  }

int main()
{
  // variable declarations
  long long int i;
  long long int j;
  long long int k;
  long long int n;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    k = buf[1];
    n = buf[2];
    i = buf[3];
    j = buf[4];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
             "i", i, "j", j, "k", k, "n", n);

    // pre-conditions
    assume((-10000 <= k && k <= 10000));
    assume((-10000 <= n && n <= 10000));
    // precheck
    // loopcond : (i <= n)

    if (choices > 15000)
    {
      //pre-conditions
      assume((preflag == 0));
      (i = 0);
      (j = 0);
      precount++;
      precheck(fptr, vars, i, j, k, n);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j, k, n));

      // Loop Condition
      if ((i <= n))
      {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((i <= n) && unroll--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_i = i;
          long long int temp_j = j;
          {
            {
              (i = (i + 1));
              (j = (j + i));
            }
          }

          loopcount++;
          loopcheck(fptr, vars, temp_i, temp_j, i, j, k, n);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, (((i + (j + k)) > (2 * n))), i, j, k, n)
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