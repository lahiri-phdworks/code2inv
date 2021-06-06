#include <8.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag)                                                   \
  if (!cond)                                                                   \
    flag = 1;

#define assume(cond)                                                           \
  if (!cond)                                                                   \
    continue;

#define INV(x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int x, long long int y) {
  int f = preflag;
  aflcrash(INV(x, y), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(file_descp, "Pre : %s : %lld, %s : %lld\n", "x", x, "y", y);
    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_x,
               long long int temp_y, long long int x, long long int y) {
  int f = loopflag;
  aflcrash(INV(x, y), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld\n", "x", temp_x, "y",
            temp_y);
    fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld\n", "x", x, "y", y);
    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, y)                                \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(file_descp, "Post : %s : %lld, %s : %lld\n", "x", x, "y", y);  \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int main() {
  // variable declarations
  long long int x;
  long long int y;

  char buff[2048];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 2048);

  for (;;) {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];
    y = buf[1];
    x = buf[2];

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld", "x", x, "y", y);

    // pre-conditions
    // precheck
    // loopcond : unknown()

    if (choices > 10000) {
      // pre-conditions
      assume((preflag == 0));
      assume((x >= 0));
      assume((x <= 10));
      assume((y <= 10));
      assume((y >= 0));
      precount++;
      precheck(fptr, vars, x, y);
    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(x, y));

      // Loop Condition
      if (choices > 2500) {
        // Bounded Unrolling
        int k = UNROLL_LIMIT;
        while ((choices > 2500) && k--) {
          assume((loopflag == 0));
          // loop body
          long long int temp_x = x;
          long long int temp_y = y;
          {
            {
              (x = (x + 10));
              (y = (y + 10));
            }
          }
          loopcount++;
          loopcheck(fptr, vars, temp_x, temp_y, x, y);
        }
      } else {
        // post-condition
        // post-check program
        assume((postflag == 0));
        if (y == 0) {
          postcount++;
          postcheck(fptr, vars, (x != 20), x, y)
        }
      }
    }

    if (preflag + loopflag + postflag == 0 && counter == 100) {
      fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount,
              "loopcount", loopcount, "postcount", postcount);
      counter = 0;
    }

    if (preflag + loopflag + postflag >= 3) {
      fclose(fptr);
      assert(0);
    }
  }

  fclose(fptr);
  return 0;
}