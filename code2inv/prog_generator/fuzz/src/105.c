#include <105.h>
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

#define INV(n, v1, v2, v3, x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int n, long long int v1, long long int v2, long long int v3, long long int x)
{
  int f = preflag;
  aflcrash(INV(n, v1, v2, v3, x), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_n, long long int temp_x,
               long long int n, long long int v1, long long int v2, long long int v3, long long int x)
{
  int f = loopflag;
  aflcrash(INV(n, v1, v2, v3, x), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", temp_n, "v1", v1, "v2", v2, "v3", v3, "x", temp_x);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, n, v1, v2, v3, x) \
  \ 
{                                                        \
    \ 
    int f = postflag;                                       \
    \ 
   aflcrash(cond, postflag);                                \
    \ 
    if (f == 0 && postflag == 1)                            \
    {                                                       \
      \ 
        fprintf(file_descp, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
             "n",                                           \
                n, "v1", v1, "v2", v2, "v3", v3, "x", x);   \
      assert(0);                                            \
    }                                                       \
  }

int main()
{
  // variable declarations
  long long int n;
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
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    n = buf[1];
    x = buf[2];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
             "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x);

    // pre-conditions
    // precheck
    // loopcond : (x < n)

    if (choices > 10000)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 0);
      precount++;
      precheck(fptr, vars, n, v1, v2, v3, x);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, v1, v2, v3, x));

      // Loop Condition
      if ((x < n))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < n) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_n = n;
          long long int temp_x = x;
          {
            {
              (x = (x + 1));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, temp_n, temp_x, n, v1, v2, v3, x);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((n >= 0))
        {
          postcount++;
          postcheck(fptr, vars, (x == n), n, v1, v2, v3, x)
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