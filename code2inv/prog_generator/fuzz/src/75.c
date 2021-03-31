#include <75.h>
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

#define INV(c, x1, x2, x3, y, z) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int c, long long int x1, long long int x2, long long int x3, long long int y, long long int z)
{
  int f = preflag;
  aflcrash(INV(c, x1, x2, x3, y, z), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(file_descp, "Pre : %s\n",
            buff);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int c, long long int x1, long long int x2, long long int x3, long long int y, long long int z)
{
  int f = loopflag;
  aflcrash(INV(c, x1, x2, x3, y, z), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(file_descp, "Loop : %s\n",
            buff);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, c, x1, x2, x3, y, z) \
  \ 
{                                                           \
    \ 
    int f = postflag;                                          \
    \ 
   aflcrash(cond, postflag);                                   \
    \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(file_descp, "Post : %s\n", buff); \ 
}           \
  }

int main()
{
  // variable declarations
  long long int c;
  long long int x1;
  long long int x2;
  long long int x3;
  long long int y;
  long long int z;

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
    y = buf[1];
    c = buf[2];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld", "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      assume((y >= 0));
      assume((y >= 127));
      (c = 0);
      (z = (36 * y));
      precount++;
      precheck(fptr, vars, c, x1, x2, x3, y, z);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(c, x1, x2, x3, y, z));

      // Loop Condition
      if ((choices > 55))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((choices > 55) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            if ((c < 36))
            {
              (z = (z + 1));
              (c = (c + 1));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, c, x1, x2, x3, y, z);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((c < 36))
        {
          postcount++;
          postcheck(fptr, vars, (z < 4608), c, x1, x2, x3, y, z)
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
      assert(0);
  }
}