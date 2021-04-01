#include <41.h>
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

#define INV(n, c) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int n, long long int c)
{
  int f = preflag;
  aflcrash(INV(n, c), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_n,
               long long int temp_c, long long int n, long long int c)
{
  int f = loopflag;
  aflcrash(INV(n, c), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld\n",
            "n", temp_n, "c", temp_c);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld\n",
            "n", n, "c", c);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, n, c)      \
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
  long long int c;
  long long int n;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  for (;;)
  {
    size_t len;
    const int32_t *buf;

    HF_ITER(&buf, &len);

    long long int choices = buf[0];
    n = buf[1];
    c = buf[2];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld", "n", n, "c", c);

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      assume((n > 0));
      precount++;
      precheck(fptr, vars, n, c);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(n, c));

      // Loop Condition
      if ((choices > 55))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((choices > 55) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_n = n;
          long long int temp_c = c;
          {
            {
              if (choices > 64)
              {
                if ((c > n))
                {
                  (c = (c + 1));
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
          loopcheck(fptr, vars, temp_n, temp_c, n, c);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c != n))
        {
          postcount++;
          postcheck(fptr, vars, (c <= n), n, c)
        }
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount", loopcount, "postcount", postcount);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}