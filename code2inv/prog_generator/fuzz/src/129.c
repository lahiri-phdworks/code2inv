#include <129.h>
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

#define INV(x, y) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int x, long long int y)
{
  int f = preflag;
  aflcrash(INV(x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_x,
               long long int temp_y, long long int x, long long int y)
{
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld\n",
            "x", temp_x, "y", temp_y);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld\n",
            "x", x, "y", y);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, y)      \
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
  long long int x;
  long long int y;
  long long int z1;
  long long int z2;
  long long int z3;

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
    y = buf[1];
    x = buf[2];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld", "x", x, "y", y);

    // pre-conditions
    // precheck
    // loopcond : (x < y)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = 1);
      precount++;
      precheck(fptr, vars, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y));

      // Loop Condition
      if ((x < y))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x < y) && k--)
        {
          assume((loopflag == 0));
          long long int temp_x = x;
          long long int temp_y = y;
          {
            {
              (x = (x + x));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, temp_x, temp_y, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        {
          postcount++;
          postcheck(fptr, vars, (x >= 1), x, y)
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