#include <96.h>
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

#define INV(i, j, x, y) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int i, long long int j, long long int x, long long int y)
{
  int f = preflag;
  aflcrash(INV(i, j, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "j", j, "x", x, "y", y);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_i, long long int temp_j, long long int temp_x, long long int temp_y,
               long long int i, long long int j, long long int x, long long int y)
{
  int f = loopflag;
  aflcrash(INV(i, j, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", temp_i, "j", temp_j, "x", temp_x, "y", temp_y);

    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "j", j, "x", x, "y", y);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, i, j, x, y)                                  \
  \ 
{                                                                                   \
    \ 
    int f = postflag;                                                                  \
    \ 
   aflcrash(cond, postflag);                                                           \
    \ 
    if (f == 0 && postflag == 1)                                                       \
    {                                                                                  \
      \ 
            fprintf(file_descp, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \
                    "i", i, "j", j, "x", x, "y", y);                                   \
    }                                                                                  \
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

  for (;;)
  {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    i = buf[1];
    y = buf[2];
    j = buf[4];
    x = buf[3];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld",
             "i", i, "j", j, "x", x, "y", y);

    // pre-conditions
    // precheck
    // loopcond : (i <= x)

    if (choices > 15000)
    {
      //pre-conditions
      assume((preflag == 0));
      (j = 0);
      (i = 0);
      (y = 1);
      precount++;
      precheck(fptr, vars, i, j, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j, x, y));

      // Loop Condition
      if ((i <= x))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((i <= x) && k--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_i = i;
          long long int temp_j = j;
          long long int temp_x = x;
          long long int temp_y = y;
          {
            {
              (i = (i + 1));
              (j = (j + y));
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
        if ((i != j))
        {
          postcount++;
          postcheck(fptr, vars, (y != 1), i, j, x, y)
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