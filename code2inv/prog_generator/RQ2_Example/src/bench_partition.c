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

int arr[] = {
    30275, 37282, 19728, 14202, 30981, 34964, 35225, 29029, 12726, 14288, 22224,
    17810, 40890, 30525, 18610, 17636, 639,   22793, 41929, 6930,  37793, 40682,
    26551, 23400, 47861, 28289, 47665, 16693, 8459,  25072, 39761, 45713, 41436,
    18520, 31020, 8874,  37772, 13876, 46522, 22847, 46843, 6869,  42096, 17599,
    7962,  22609, 3899,  41449, 9876,  13447, 20928, 8195,  41558, 46424, 40821,
    38037, 46952, 22604, 22349, 29748, 4361,  33273, 32482, 4204,  9194,  16303,
    14246, 33888, 18164, 12097, 9954,  16318, 44492, 40478, 17146, 896,   25681,
    12308, 26933, 39945, 11685, 7385,  19020, 43389, 6913,  855,   28428, 49831,
    24348, 3546,  18646, 34548, 42056, 18718, 16975, 36827, 8916,  20775, 9346,
    21975, 40189, 25784, 45088, 41229, 46242, 40434, 22567, 49891, 38903, 17173,
    39038, 6125,  39923, 7903,  2889,  31847, 34684, 19417, 30799, 27291, 12400,
    17624, 22147, 27511, 33461, 1139,  45342, 33901, 9796,  3706,  24631, 30204,
    37971, 21590, 36420, 6796,  10227, 26049, 21494, 22027, 48954, 1223,  48433,
    30656, 23437, 39570, 22249, 13314, 20331, 44704, 8450,  15023, 39331, 25721,
    22588, 6958,  34286, 24700, 46697, 29829, 3457,  26478, 9937,  42539, 38051,
    16165, 42492, 40049, 33325, 10856, 25218, 9372,  36599, 28829, 46519, 29314,
    519,   1839,  19734, 25844, 47766, 9043,  14825, 39026, 47420, 15647, 14415,
    47670, 30070, 33611, 46627, 44063, 30199, 32441, 21371, 22928, 16281, 11302,
    33776, 33415, 4341,  29055, 23241, 2892,  48098, 2388,  32545, 13948, 45054,
    20884, 46467, 1893,  39887, 47390, 29466, 23081, 3650,  28059, 29640, 34737,
    45448, 20401, 16604, 15551, 32112, 49622, 40675, 34575, 24767, 30036, 40587,
    1936,  13764, 39598, 40147, 39878, 29660, 24558, 31053, 29754, 1005,  43932,
    27860, 37402, 43300, 49146, 36931, 24467, 1928,  46343, 36308, 7844,  24040,
    12337, 38693, 5027,  14187, 40793, 13216, 40226, 18023, 19620, 27370, 41578,
    24373, 15399, 19208, 16815, 5650,  41682, 27360, 4668,  4389,  2674,  23649,
    9643,  43057, 2542,  49417, 3807,  38132, 13576, 39298, 37955, 12157, 38947,
    32893, 11220, 38432, 25601, 30568, 36903, 35090, 16430, 38282, 35790, 48015,
    16316, 17979, 37740};

#define INV(i, pivot, high, right) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int i, long long int pivot,
              long long int high, long long int right) {
  int f = preflag;
  aflcrash(INV(i, pivot, high, right), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i,
            "pivot", pivot, "high", high, "right", right);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_i,
               long long int temp_pivot, long long int temp_high,
               long long int temp_right, long long int i, long long int pivot,
               long long int high, long long int right) {
  int f = loopflag;
  aflcrash(INV(i, pivot, high, right), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", temp_i, "pivot", temp_pivot, "high", temp_high, "right",
            temp_right);
    fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i",
            i, "pivot", pivot, "high", high, "right", right);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, pivot, high, right)                     \
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
 "i",                                                                          \
                i, "pivot", pivot, "high", high, "right", right);              \
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
  unsigned int right;

  char buff[1024];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 1024);

  // freopen("models.txt", "w", stderr);

  for (;;) {
    size_t len;
    const uint8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    int choices = buff[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i,
             "pivot", pivot, "high", high, "right", right);

    // pre-conditions
    i = buf[1];
    j = buff[2];
    high = buff[3];
    right = 0;
    pivot = arr[buff[4]];
    // precheck
    // loopcond : (j <= high - 1)

    // Honggfuzz Specific Assume for sanity
    assume((i > 0));

    if (buff[0] > 90) {
      // pre-conditions
      high = (int)((sizeof(arr) / sizeof(arr[0])) - 1);
      select_pivot(arr, 0, high);
      pivot = arr[high];
      assume((i > 0));
      j = 0;
      right = 0;
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, i, pivot, high, right);

    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(i, pivot, high, right));

      // Loop Condition
      if (j <= high - 1) {
        // fprintf(fptr, "LOP : %d, %d, %d, %d. %d\n", i, j, high, pivot,
        //         choices);
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;
        while ((j <= high - 1) && unroll--) {
          assume((loopflag == 0));
          int temp_i = i, temp_pivot = pivot, temp_right = right,
              temp_high = high;
          // loop body
          if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i = i + 1;
          }
          j = j + 1;

          loopcount++;
          loopcheck(fptr, vars, temp_i, temp_pivot, temp_high, temp_right, i,
                    pivot, high, right);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        swap(&arr[i], &arr[high]);
        // fprintf(fptr, "__POTSL__ : %d, %d, %d, %d. %d\n", i, j, high, pivot,
        //         choices);
        // post-condition
        postcount++;
        postcheck(fptr, vars, ((0 < i <= right) && (arr[i - 1] <= pivot)), i,
                  pivot, high, right)
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