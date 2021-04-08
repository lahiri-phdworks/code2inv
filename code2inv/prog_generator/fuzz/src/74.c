#include <74.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 512

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
void precheck(FILE *fptr, char *buff, long long int c, long long int x1, long long int x2, long long int x3, long long int y, long long int z)
{
  int f = preflag;
  aflcrash(INV(c, x1, x2, x3, y, z), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_c, long long int temp_y, long long int temp_z,
               long long int c, long long int x1, long long int x2, long long int x3, long long int y, long long int z)
{
  int f = loopflag;
  aflcrash(INV(c, x1, x2, x3, y, z), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "c", temp_c, "x1", x1, "x2", x2, "x3", x3, "y", temp_y, "z", temp_z);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, c, x1, x2, x3, y, z)             \
  \ 
{                                                                 \
    \ 
    int f = postflag;                                                \
    \ 
   aflcrash(cond, postflag);                                         \
    \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "c",                                                                \
                c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z); \ 
} \
  }

long long int func(long long int a, long long int b)
{
  return a + b;
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

  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int32_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    c = buf[1];
    y = buf[2];
    z = buf[3];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
             "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);

    // pre-conditions
    // precheck
    // loopcond : (unknown())

    if (choices > 30000)
    {
      //pre-conditions
      assume((preflag == 0));
      (c = 0);
      assume((y >= 0));
      assume((y >= 127));
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
      if ((choices > 1500))
      {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((choices > 1500) && unroll--)
        {
          assume((loopflag == 0));
          long long int temp_c = c;
          long long int temp_y = y;
          long long int temp_z = z;
          {
            // loop body
            if ((c < 36))
            {
              (z = (func(z, 1)));
              (c = (func(c, 1)));
            }
          }

          loopcount++;
          loopcheck(fptr, vars, temp_c, temp_y, temp_z, c, x1, x2, x3, y, z);
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
          postcheck(fptr, vars, ((z >= 0)), c, x1, x2, x3, y, z)
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