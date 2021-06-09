#include <assert.h>
#include <bench_partition.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 32

#define aflcrash(cond, flag)                                                   \
  if (!cond)                                                                   \
    flag = 1;

#define assume(cond)                                                           \
  if (!cond)                                                                   \
    continue;

#define INV(i, j, high) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int i, long long int j,
              long long int high) {
  int f = preflag;
  aflcrash(INV(i, j, high), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j,
            "high", high);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_i,
               long long int temp_j, long long int temp_high, long long int i,
               long long int j, long long int high) {
  int f = loopflag;
  aflcrash(INV(i, j, high), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i,
            "j", temp_j, "high", temp_high);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j,
            "high", high);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, j, high)                                \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                                                          \
                i, "j", j, "high", high);                                      \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int main() {
  // variable declarations
  int i;
  int j;
  int pivot;
  int high;

  // partition over a static array.
  int arr[] = {2, 3, 90, 78, 1, 0, 67, 14, 9, 6, 7, 18, 10, 15, 11};

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const int16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j,
             "high", high);

    // pre-conditions
    i = buf[1];
    j = buf[2];
    high = (int)((sizeof(arr) / sizeof(arr[0])) - 1);
    pivot = arr[high];
    // precheck
    // loopcond : (j <= high - 1)

    if (choices > 15000) {
      // pre-conditions
      select_pivot(arr, 0, high);
      pivot = arr[high];
      i = 0;
      j = 0;
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, i, j, high);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, j, high));

      // Loop Condition
      if (j <= high - 1) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((j <= high - 1) && unroll--) {
          assume((loopflag == 0));
          int temp_i = i, temp_j = j, temp_high = high;

          // loop body
          if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i = i + 1;
          }
          j = j + 1;

          loopcount++;
          loopcheck(fptr, vars, temp_i, temp_j, temp_high, i, j, high);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        swap(&arr[i], &arr[high]);

        // post-condition
        postcount++;
        postcheck(fptr, vars,
                  ((0 <= i <= high) && (arr[i - 1] < pivot) &&
                   (arr[i] == pivot) && (arr[i + 1] > pivot)),
                  i, j, high)
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