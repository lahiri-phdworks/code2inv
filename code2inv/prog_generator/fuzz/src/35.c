#include <35.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/file.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 100

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
void precheck(FILE *file_descp, char *buff, long long int c)
{
  int f = preflag;
  aflcrash(INV(c), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s : %lld\n", "c", c);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_c, long long int c)
{
  int f = loopflag;
  aflcrash(INV(c), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld\n",
            "c", temp_c);
    fprintf(file_descp, "LoopEnd : %s : %lld\n",
            "c", c);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, c)               \
  \ 
{                                                       \
    \ 
    int f = postflag;                                      \
    \ 
   aflcrash(cond, postflag);                               \
    \ 
    if (f == 0 && postflag == 1)                           \
    {                                                      \
      \ 
        fprintf(file_descp, "Post : %s : %lld\n", "c", c); \
      assert(0);                                           \
    }                                                      \
  }

int main()
{
  // variable declarations
  long long int c;

  char buff[512];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 512);

  for (;;)
  {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    c = buf[1];

    char vars[32];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 32, "%s : %lld", "c", c);

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
      if ((choices > 2500))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((choices > 2500) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_c = c;
          {
            {
              if (choices > 5000)
              {
                if ((c != 40))
                {
                  (c = (c + 1));
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
          postcheck(fptr, vars, (c >= 0), c)
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