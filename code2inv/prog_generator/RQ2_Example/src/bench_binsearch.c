#include <assert.h>
#include <bench_binsearch.h>
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

#define INV(low, mid, high, item) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int low, long long int mid,
              long long int high, long long int item) {
  int f = preflag;
  aflcrash(INV(low, mid, high, item), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "low",
            low, "mid", mid, "high", high, "item", item);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_low,
               long long int temp_mid, long long int temp_high,
               long long int temp_item, long long int low, long long int mid,
               long long int high, long long int item) {
  int f = loopflag;
  aflcrash(INV(low, mid, high, item), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "low", temp_low, "mid", temp_mid, "high", temp_high, "item",
            temp_item);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "low", low, "mid", mid, "high", high, "item", item);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, low, mid, high, item)                      \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "low",                                                                        \
                low, "mid", mid, "high", high, "item", item);                  \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int main() {
  // variable declarations
  int low;
  int high;
  int mid;
  int item;
  int SIZE;
  int arr[] = {5,   6,   11,  18,  23,  28,  29,  30,  35,  33,  88,
               89,  90,  95,  105, 115, 125, 162, 189, 196, 225, 345,
               382, 412, 430, 445, 500, 505, 519, 569, 725, 885, 1025};

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const uint16_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "low",
             low, "mid", mid, "high", high, "item", item);

    // pre-conditions
    low = buf[1];
    item = buf[3];
    mid = buf[4];
    high = (int)(sizeof(arr) / sizeof(arr[0]));
    SIZE = (int)(sizeof(arr) / sizeof(arr[0]));
    // precheck
    // loopcond : (low < high)

    if (choices > 15000) {
      // pre-conditions
      low = 0;
      mid = 0;
      item = 0;
      high = (int)(sizeof(arr) / sizeof(arr[0]));
      SIZE = (int)(sizeof(arr) / sizeof(arr[0]));
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, low, mid, high, item);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(low, mid, high, item));

      // Loop Condition
      if (low < high) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;

        while ((low < high) && unroll--) {
          assume((loopflag == 0));

          int temp_low = low, temp_mid = mid, temp_high = high,
              temp_item = item;

          // loop body
          mid = (low + high) / 2;
          if ((item < arr[mid])) {
            high = mid;
          } else if ((arr[mid] < item)) {
            low = mid + 1;
          } else {
            break;
          }

          loopcount++;
          loopcheck(fptr, vars, temp_low, temp_mid, temp_high, temp_item, low,
                    mid, high, item);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        postcount++;
        postcheck(fptr, vars,
                  ((0 <= low <= mid <= high) &&
                   (((0 <= mid) && (mid < low) && (arr[mid] != item)) ||
                    ((high <= mid) && (mid <= SIZE) && (arr[mid] != item)) ||
                    (arr[mid] == item))),
                  low, mid, high, item)
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