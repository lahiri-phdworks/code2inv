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

#define INV(i, pivot, high, right) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

int arr[] = {
    13783, 8394,  18532, 25598, 14544, 18023, 25257, 8069,  2786,  24992, 29211,
    17553, 2866,  4396,  26790, 9937,  4914,  17861, 9590,  24304, 17957, 26061,
    19667, 3805,  10630, 1250,  9235,  3773,  5769,  16344, 30922, 11034, 20311,
    22070, 28599, 1223,  2193,  16812, 24217, 26323, 26098, 29097, 29089, 5782,
    21622, 31788, 12541, 28250, 19917, 18599, 25491, 9214,  12889, 29028, 29814,
    15754, 24071, 20070, 11626, 27689, 15552, 29803, 1160,  15528, 6418,  24061,
    26794, 4599,  18670, 28968, 2154,  26687, 23795, 11264, 3274,  5588,  8022,
    8070,  6035,  20166, 15013, 27294, 19204, 4353,  2550,  29949, 3204,  9716,
    6689,  13852, 20852, 14943, 10302, 19175, 31122, 18905, 1539,  14272, 23423,
    29611, 17395, 18003, 29466, 19814, 28774, 16411, 7442,  13513, 10134, 23789,
    10425, 14066, 16153, 30532, 20823, 27315, 11423, 14689, 7103,  28995, 20741,
    2488,  15961, 15899, 29720, 23757, 28293, 7620,  16544, 7747,  28558, 15524,
    20234, 9340,  16364, 20660, 7808,  30095, 26477, 6042,  12564, 7623,  17379,
    2101,  12550, 7677,  17684, 12533, 19356, 21237, 8886,  5309,  3460,  29317,
    22019, 16705, 10298, 16763, 10094, 18659, 22573, 29837, 1533,  30855, 23906,
    6017,  24401, 5184,  26876, 20812, 28151, 29395, 6763,  24288, 24005, 12384,
    8257,  1195,  7265,  1135,  16338, 24468, 3989,  9868,  9979,  7299,  16763,
    22188, 26905, 22085, 8466,  31170, 1105,  21871, 21179, 17209, 14554, 11456,
    3109,  8465,  29439, 14068, 19772, 15555, 16984, 23198, 22511, 1230,  2763,
    26196, 30315, 4790,  20226, 4732,  20044, 4610,  27826, 10503, 2884,  22508,
    26775, 17246, 12005, 30694, 27905, 19187, 16538, 7137,  7105,  22809, 26647,
    7429,  25798, 22198, 11480, 8166,  19100, 22707, 1184,  1781,  2291,  3050,
    28512, 18683, 26658, 26062, 27595, 8569,  30904, 9837,  7951,  14519, 6390,
    10224, 31695, 23854, 20072};

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

void swap(int *term1, int *term2) {
  int temp = *term1;
  *term1 = *term2;
  *term2 = temp;
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

    srand(time(0));

    size_t len;
    const uint8_t *buf;

    HF_ITER(&buf, &len);
    counter++;

    // COMMENT : Honggfuzz Specific
    assume((len > 6));
    int choices = buf[len - 1];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i,
             "pivot", pivot, "high", high, "right", right);

    // pre-conditions
    i = buf[4];
    j = buf[1];
    high = buf[3];
    right = i;
    pivot = arr[high];
    // precheck
    // loopcond : (j <= high - 1)

    // Honggfuzz Specific Assume for sanity
    assume((i > 0));

    // fprintf(fptr, "__BEGIN__ : %d, %d, %d, %d. %d\n", i, j, high, pivot,
    //         choices);

    if (choices > 75) {
      // pre-conditions
      // fprintf(fptr, "__PRE__ : %d, %d, %d, %d. %d\n", i, j, high, pivot,
      //         choices);
      high = (int)((sizeof(arr) / sizeof(arr[0])) - 1);
      select_pivot(arr, 0, high);
      pivot = arr[high];
      assume((i > 0));
      i = 1;
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
        // fprintf(fptr, "__LOOP__ : %d, %d, %d, %d. %d\n", i, j, high, pivot,
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
            right++;
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
        // fprintf(fptr, "__POST__ : %d, %d, %d, %d. %d\n", i, j, high, pivot,
        //         choices);
        // post-condition
        postcount++;
        postcheck(fptr, vars, ((0 < i <= right) && (arr[i] == pivot)), i, pivot,
                  high, right)
      }
    }

    if (preflag + loopflag + postflag == 0 && counter > 100) {
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
  assert(0);
  return 0;
}