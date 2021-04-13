#include <70.h>
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

#define INV(n, v1, v2, v3, x, y) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int n, long long int v1, long long int v2, long long int v3, long long int x, long long int y)
{
  int f = preflag;
  aflcrash(INV(n, v1, v2, v3, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_n, long long int temp_y, long long int temp_x,
               long long int n, long long int v1, long long int v2, long long int v3, long long int x, long long int y)
{
  int f = loopflag;
  aflcrash(INV(n, v1, v2, v3, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", temp_n, "v1", v1, "v2", v2, "v3", v3, "x", temp_x, "y", temp_y);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, n, v1, v2, v3, x, y)          \
  \ 
{                                                              \
    \ 
    int f = postflag;                                             \
    \ 
   aflcrash(cond, postflag);                                      \
    \ 
    if (f == 0 && postflag == 1)                                  \
    {                                                             \
      \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "n",                                                             \
                n, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y); \
      assert(0);                                                  \
    \ 
}                                                            \
  }

int main()
{
  // variable declarations
  long long int n;
  long long int v1;
  long long int v2;
  long long int v3;
  long long int x;
  long long int y;

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
    n = buf[1];
    x = buf[2];
    y = buf[3];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
             "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);

    // pre-conditions
    // precheck
    // loopcond : (x <= n)

    if (choices > 10000)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 1);
      precount++;
      precheck(fptr, vars, n, v1, v2, v3, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, v1, v2, v3, x, y));

      // Loop Condition
      if ((x <= n))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x <= n) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_n = n;
          long long int temp_x = x;
          long long int temp_y = y;
          {
            y = n - x;
            x = x + 1;
          }

          loopcount++;
          loopcheck(fptr, vars, temp_n, temp_x, temp_y, n, v1, v2, v3, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if (n > 0)
        {
          // assert (y >= 0);
          postcount++;
          postcheck(fptr, vars, (y < n), n, v1, v2, v3, x, y)
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