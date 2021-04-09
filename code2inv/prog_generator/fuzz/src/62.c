#include <62.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 1024

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(c, n, v1, v2, v3) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int c, long long int n, long long int v1, long long int v2, long long int v3)
{
  int f = preflag;
  aflcrash(INV(c, n, v1, v2, v3), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_c, long long int temp_n,
               long long int c, long long int n, long long int v1, long long int v2, long long int v3)
{
  int f = loopflag;
  aflcrash(INV(c, n, v1, v2, v3), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "c", temp_c, "n", temp_n, "v1", v1, "v2", v2, "v3", v3);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, c, n, v1, v2, v3)        \
  \ 
{                                                         \
    \ 
    int f = postflag;                                        \
    \ 
   aflcrash(cond, postflag);                                 \
    \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "c",                                                        \
                c, "n", n, "v1", v1, "v2", v2, "v3", v3); \ 
} \
  }

long long int func(long long int a, long long int b)
{
  long long int c = 0;
  __asm__ __volatile__("addl %%ebx, %%eax;"
                       : "=a"(c)
                       : "a"(a), "b"(b));
  return c;
}

int main()
{
  // variable declarations
  long long int c;
  long long int n;
  long long int v1 = 512;
  long long int v2 = 512;
  long long int v3 = 512;

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
    c = buf[1];
    n = buf[2];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
             "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 15000)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      assume((n > 0));
      precount++;
      precheck(fptr, vars, c, n, v1, v2, v3);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(c, n, v1, v2, v3));

      // Loop Condition
      if ((choices > 1500))
      {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((choices > 1500) && unroll--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_c = c;
          long long int temp_n = n;
          {
            {
              if (choices > 1500)
              {
                if ((c != n))
                {
                  (c = (func(c, 1)));
                }
              }
              else
              {
                if ((c == n))
                {
                  (c = 1);
                }
              }
            }
          }

          loopcount++;
          loopcheck(fptr, vars, temp_c, temp_n, c, n, v1, v2, v3);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((n > -1))
        {
          postcount++;
          postcheck(fptr, vars, ((c != n)), c, n, v1, v2, v3)
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