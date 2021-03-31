#include <89.h>
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

#define INV(lock, v1, v2, v3, x, y) PHI

int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff,
              int lock, int v1, int v2, int v3, int x, int y)
{
  int f = preflag;
  aflcrash(INV(lock, v1, v2, v3, x, y), preflag);
  if (f == 0 && preflag == 1)
  {
    flock(fileno(file_descp), LOCK_SH);
    fprintf(file_descp, "\nPre : %s\n",
            buff);
    flock(fileno(file_descp), LOCK_UN);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff,
               int lock, int v1, int v2, int v3, int x, int y)
{
  int f = loopflag;
  aflcrash(INV(lock, v1, v2, v3, x, y), loopflag);
  if (f == 0 && loopflag == 1)
  {
    flock(fileno(file_descp), LOCK_SH);
    fprintf(file_descp, "\nLoop : %s\n",
            buff);
    flock(fileno(file_descp), LOCK_UN);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, lock, v1, v2, v3, x, y) \
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
        flock(fileno(fptr), LOCK_SH);                       \
      fprintf(fptr, "\nPost : %s\n", buff);                 \
      flock(fileno(fptr), LOCK_UN);                         \
    }                                                       \
  }

int main()
{
  // variable declarations
  long long int lock;
  long long int v1;
  long long int v2;
  long long int v3;
  long long int x;
  long long int y;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));
  FILE *fptr = fopen("models.txt", "w");

  // COMMENT : This must be line buffered.
  setvbuf(fptr, buff, _IOLBF, 1024);

  for (;;)
  {
    size_t len;
    const int32_t *buf;

    HF_ITER(&buf, &len);

    int choices = buf[0];
    y = buf[1];
    x = buf[2];
    lock = buf[3];

    char vars[150];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 150, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld",
             "lock", lock, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);

    // pre-conditions
    assume((-10000 <= y && y <= 10000));
    // precheck
    // loopcond : (x != y)

    if (choices > 25)
    {
      //pre-conditions
      assume((preflag == 0));
      (x = y);
      (lock = 1);
      precount++;
      precheck(fptr, vars, lock, v1, v2, v3, x, y);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(lock, v1, v2, v3, x, y));

      // Loop Condition
      if ((x != y))
      {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((x != y) && k--)
        {
          assume((loopflag == 0));
          // loop body
          {
            {
              if (choices > 63)
              {
                {
                  (lock = 1);
                  (x = y);
                }
              }
              else
              {
                {
                  (lock = 0);
                  (x = y);
                  (y = (y + 1));
                }
              }
            }
          }
          loopcount++;
          loopcheck(fptr, vars, lock, v1, v2, v3, x, y);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars, (lock == 1), lock, v1, v2, v3, x, y)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100)
    {
      fprintf(fptr, "\n%s : %lld, %s : %lld, %s : %lld\n",
              "precount", precount, "loopcount", loopcount, "postcount", postcount);
      // fflush(file_descp);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3)
      assert(0);
  }
}