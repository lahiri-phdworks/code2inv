#include <36.h>
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

#define INV(c) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int c)
{
  int f = preflag;
  aflcrash(INV(c), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(fptr, "Pre : %s : %lld\n",
            "c", c);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_c, long long int c)
{
  int f = loopflag;
  aflcrash(INV(c), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(fptr, "LoopStart : %s : %lld\n",
            "c", temp_c);
    fprintf(fptr, "LoopEnd : %s : %lld\n",
            "c", c);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, c) \
  \ 
{                                   \
    \ 
    int f = postflag;                  \
    \ 
   aflcrash(cond, postflag);           \
    \ 
    if (f == 0 && postflag == 1)       \
    {                                  \
      \ 
        fprintf(fptr, "Post : %s : %lld\n", \ 
 "c",                                  \
                c);                    \
      assert(0);                       \
    \ 
}                                 \
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
    c = buf[2];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld\n",
             "c", c);

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 10000)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      precount++;
      precheck(fptr, vars, c);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(c));

      // Loop Condition
      if ((choices > 1500))
      {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((choices > 1500) && unroll--)
        {
          assume((loopflag == 0));
          long long int temp_c = c;
          // loop body
          {

            {
              if (choices > 1500)
              {
                if ((c != 40))
                {
                  (c = (func(c, 1)));
                }
              }
              else
              {
                if ((c == 40))
                {
                  (c = 1);
                }
              }
            }
          }

          loopcount++;
          loopcheck(fptr, vars, temp_c, c);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c != 40))
        {
          postcount++;
          postcheck(fptr, vars, ((c <= 40)), c)
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