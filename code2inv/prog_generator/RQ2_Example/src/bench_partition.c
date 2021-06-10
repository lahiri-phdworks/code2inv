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

#define INV(i, pivot, high) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, int arr[], long long int i,
              long long int pivot, long long int high) {
  int f = preflag;
  aflcrash(INV(i, pivot, high), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "i", i, "pivot",
            pivot, "high", high);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, int arr[], long long int temp_i,
               long long int temp_pivot, long long int temp_high,
               long long int i, long long int pivot, long long int high) {
  int f = loopflag;
  aflcrash(INV(i, pivot, high), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i,
            "pivot", temp_pivot, "high", temp_high);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "i", i,
            "pivot", pivot, "high", high);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, pivot, high)                            \
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
                i, "pivot", pivot, "high", high);                              \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void select_pivot(int arr[], int low, int high) {
  srand(time(0));
  int random = low + rand() % (high - low);
  swap(&arr[random], &arr[high]);
}

int main() {
  // variable declarations
  unsigned int i;
  unsigned int j;
  unsigned int pivot;
  unsigned int high;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  int arr[] = {
      5635,  23603, 14648, 38589, 32615, 21232, 30243, 38129, 37528, 29670,
      29608, 30578, 18009, 6714,  13134, 16255, 7272,  33956, 49616, 22017,
      17945, 21296, 15528, 43967, 33025, 39392, 25605, 38979, 42893, 5417,
      41259, 26219, 116,   39869, 12294, 43979, 29123, 49269, 31633, 46341,
      8384,  44378, 28027, 3527,  4752,  2744,  41968, 22258, 49319, 48857,
      474,   22037, 18644, 11799, 45095, 7294,  1758,  33638, 31851, 4494,
      4384,  33896, 36712, 45801, 12671, 38417, 47317, 30202, 13561, 23792,
      37150, 17542, 13529, 8714,  4946,  25588, 27049, 6364,  26011, 33291,
      49679, 1753,  23092, 1111,  28310, 48640, 24912, 46288, 28874, 22484,
      8714,  38813, 9226,  8957,  10993, 49919, 32007, 24382, 9301,  41976,
      34522, 9177,  19022, 15577, 43730, 30807, 12237, 31521, 32300, 39661,
      26851, 34386, 20315, 22967, 1926,  34977, 44411, 43013, 39580, 3445,
      1638,  23221, 47602, 1898,  26588, 44225, 43610, 40120, 45018, 25383,
      39427, 36572, 34906, 5874,  14566, 46718, 1605,  12029, 4419,  15737,
      47801, 45088, 25739, 44134, 32778, 49684, 27713, 17514, 41911, 5503,
      19350, 42390, 34623, 39229, 27150, 8062,  46576, 27717, 22161, 8652,
      24525, 27145, 4194,  9569,  28703, 48658, 1431,  116,   41131, 3289,
      32579, 35594, 39322, 36556, 2136,  7926,  41690, 32950, 7177,  38946,
      3183,  22370, 46721, 46256, 16450, 46997, 30649, 28870, 33141, 14666,
      33954, 34240, 24745, 32155, 39540, 19798, 47155, 30458, 41497, 31923,
      31303, 47783, 25281, 29348, 9050,  4976,  34251, 8033,  1385,  37304,
      39098, 31799, 44930, 18012, 28395, 41707, 36779, 32423, 19078, 39433,
      49815, 3859,  43035, 36692, 14723, 39273, 7246,  6496,  45675, 23776,
      15506, 19989, 45616, 40826, 35429, 21846, 4128,  26546, 38216, 48551,
      45043, 5935,  27148, 27904, 10254, 6391,  13343, 38586, 32613, 38129,
      28414, 38311, 39021, 7295,  23799, 24940, 6883,  241,   21603, 43015,
      43521, 5437,  15812, 42887, 16727, 6753,  32770, 19652, 8860,  22255,
      25870, 16284, 20716, 12061, 47348, 14342, 8349,  39443, 2646,  25923,
      43120, 40460, 44228, 27865, 5886,  6085,  10451, 26556, 42419, 41547,
      20647, 20970, 18357, 29928, 35558, 25463, 45094, 44071, 8559,  15469};

  for (;;) {
    size_t len;
    const uint8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    long long int choices = buf[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n", "i", i, "pivot",
             pivot, "high", high);

    // pre-conditions
    i = buf[1];
    j = buf[2];
    high = buff[3];
    pivot = arr[buff[4]];
    // precheck
    // loopcond : (j <= high - 1)

    if (choices > 100) {
      // pre-conditions
      high = (int)((sizeof(arr) / sizeof(arr[0])) - 1);
      select_pivot(arr, 0, high);
      pivot = arr[high];
      i = 0;
      j = 0;
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, arr, i, pivot, high);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, pivot, high));

      // Loop Condition
      if (j <= high - 1) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((j <= high - 1) && unroll--) {
          assume((loopflag == 0));
          int temp_i = i, temp_pivot = pivot, temp_high = high;

          // loop body
          if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i = i + 1;
          }
          j = j + 1;

          loopcount++;
          loopcheck(fptr, vars, arr, temp_i, temp_pivot, temp_high, i, pivot,
                    high);
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
                  i, pivot, high)
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