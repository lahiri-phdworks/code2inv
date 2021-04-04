#include <124.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 32

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(i, j, x, y) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int i, long long int j, long long int x, long long int y)
{
  int f = preflag;
  aflcrash(INV(i, j, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "j", j, "x", x, "y", y);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_i, long long int temp_j, long long int temp_x, long long int temp_y,
               long long int i, long long int j, long long int x, long long int y)
{
  int f = loopflag;
  aflcrash(INV(i, j, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", temp_i, "j", temp_j, "x", temp_x, "y", temp_y);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "j", j, "x", x, "y", y);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, j, x, y) \
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
                i, "j", j, "x", x, "y", y); \ 
}  \
  }

int main()
{
  // variable declarations
  long long int i;
  long long int j;
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
    const int8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    x = buf[1];
    y = buf[2];
    i = buf[3];
    j = buf[4];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
             "i", i, "j", j, "x", x, "y", y);

    // pre-conditions
    assume((-10000 <= y && y <= 10000));
    assume((-10000 <= x && x <= 10000));
    // precheck
    // loopcond : (x != 0)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (i = x);
      (j = y);
      precount++;
      precheck(fptr, vars, i, j, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j, x, y));

      // Loop Condition
      if ((x != 0))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x != 0) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_x = x;
          long long int temp_y = y;
          long long int temp_i = i;
          long long int temp_j = j;
          {
            {
              (x = (x - 1));
              (y = (y - 1));
            }
          }

          loopcount++;
          loopcheck(fptr, vars, temp_i, temp_j, temp_x, temp_y, i, j, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if (i == j)
        {
          postcount++;
          postcheck(fptr, vars, (y == 0), i, j, x, y)
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