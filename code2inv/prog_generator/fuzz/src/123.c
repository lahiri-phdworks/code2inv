#include <123.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(i, size, sn) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int i, long long int size, long long int sn)
{
  int f = preflag;
  aflcrash(INV(i, size, sn), preflag);
  if (f == 0 && preflag == 1)
  {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "size", size, "sn", sn);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_i, long long int temp_size, long long int temp_sn, long long int i, long long int size, long long int sn)
{
  int f = loopflag;
  aflcrash(INV(i, size, sn), loopflag);
  if (f == 0 && loopflag == 1)
  {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n",
            "i", temp_i, "size", temp_size, "sn", temp_sn);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "size", size, "sn", sn);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, size, sn) \
  \ 
{                                             \
    \ 
    int f = postflag;                            \
    \ 
   aflcrash(cond, postflag);                     \
    \ 
    if (f == 0 && postflag == 1)                 \
    {                                            \
      \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                            \
                i, "size", size, "sn", sn);      \
      assert(0);                                 \
    \ 
}                                           \
  }

int main()
{
  // variable declarations
  long long int i;
  long long int size;
  long long int sn;

  char buff[2048];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 2048);

  // freopen("models.txt", "w", stderr);

  for (;;)
  {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    i = buf[1];
    size = buf[2];
    sn = buf[3];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n",
             "i", i, "size", size, "sn", sn);

    // pre-conditions
    // precheck
    // loopcond : (i <= size)

    if (choices > 15000)
    {
      //pre-conditions
      assume((preflag == 0));
      (sn = 0);
      (i = 1);
      precount++;
      precheck(fptr, vars, i, size, sn);
    }
    else
    {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, size, sn));

      // Loop Condition
      if ((i <= size))
      {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((i <= size) && unroll--)
        {
          assume((loopflag == 0));
          // loop body
          long long int temp_i = i;
          long long int temp_sn = sn;
          long long int temp_size = size;
          {
            {
              (i = (i + 1));
              (sn = (sn + 1));
            }
          }

          loopcount++;
          loopcheck(fptr, vars, temp_i, temp_size, temp_sn, i, size, sn);
        }
      }
      else
      {
        // post-check program
        assume((postflag == 0));
        // post-condition
        if ((sn != 0))
        {
          postcount++;
          postcheck(fptr, vars, ((sn == size)), i, size, sn)
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