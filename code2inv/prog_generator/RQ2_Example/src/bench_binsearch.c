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

int arr[] = {
    519,   639,   855,   896,   1005,  1139,  1223,  1839,  1893,  1928,  1936,
    2388,  2542,  2674,  2889,  2892,  3457,  3546,  3650,  3706,  3807,  3899,
    4204,  4341,  4361,  4389,  4668,  5027,  5650,  6125,  6796,  6869,  6913,
    6930,  6958,  7385,  7844,  7903,  7962,  8195,  8450,  8459,  8874,  8916,
    9043,  9194,  9346,  9372,  9643,  9796,  9876,  9937,  9954,  10227, 10856,
    11220, 11302, 11685, 12097, 12157, 12308, 12337, 12400, 12726, 13216, 13314,
    13447, 13576, 13764, 13876, 13948, 14187, 14202, 14246, 14288, 14415, 14825,
    15023, 15399, 15551, 15647, 16165, 16281, 16303, 16316, 16318, 16430, 16604,
    16693, 16815, 16975, 17146, 17173, 17599, 17624, 17636, 17810, 17979, 18023,
    18164, 18520, 18610, 18646, 18718, 19020, 19208, 19417, 19620, 19728, 19734,
    20331, 20401, 20775, 20884, 20928, 21371, 21494, 21590, 21975, 22027, 22147,
    22224, 22249, 22349, 22567, 22588, 22604, 22609, 22793, 22847, 22928, 23081,
    23241, 23400, 23437, 23649, 24040, 24348, 24373, 24467, 24558, 24631, 24700,
    24767, 25072, 25218, 25601, 25681, 25721, 25784, 25844, 26049, 26478, 26551,
    26933, 27291, 27360, 27370, 27511, 27860, 28059, 28289, 28428, 28829, 29029,
    29055, 29314, 29466, 29640, 29660, 29748, 29754, 29829, 30036, 30070, 30199,
    30204, 30275, 30525, 30568, 30656, 30799, 30981, 31020, 31053, 31847, 32112,
    32441, 32482, 32545, 32893, 33273, 33325, 33415, 33461, 33611, 33776, 33888,
    33901, 34286, 34548, 34575, 34684, 34737, 34964, 35090, 35225, 35790, 36308,
    36420, 36599, 36827, 36903, 36931, 37282, 37402, 37740, 37772, 37793, 37955,
    37971, 38037, 38051, 38132, 38282, 38432, 38693, 38903, 38947, 39026, 39038,
    39298, 39331, 39570, 39598, 39761, 39878, 39887, 39923, 39945, 40049, 40147,
    40189, 40226, 40434, 40478, 40587, 40675, 40682, 40793, 40821, 40890, 41229,
    41436, 41449, 41558, 41578, 41682, 41929, 42056, 42096, 42492, 42539, 43057,
    43300, 43389, 43932, 44063, 44492, 44704, 45054, 45088, 45342, 45448, 45713,
    46242, 46343, 46424, 46467, 46519, 46522, 46627, 46697, 46843, 46952, 47390,
    47420, 47665, 47670, 47766, 47861, 48015, 48098, 48433, 48954, 49146, 49417,
    49622, 49831, 49891};

unsigned int SIZE = (int)(sizeof(arr) / sizeof(arr[0]));

#define INV(low, mid, high, item, key) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int low, long long int mid,
              long long int high, long long int item, long long int key) {
  int f = preflag;
  aflcrash(INV(low, mid, high, item, key), preflag);
  if (f == 0 && preflag == 1) {
    fprintf(fptr,
            "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "low", low, "mid", mid, "high", high, "item", item, "key", key);

    assert(0);
  }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_low,
               long long int temp_mid, long long int temp_high,
               long long int temp_item, long long int temp_key,
               long long int low, long long int mid, long long int high,
               long long int item, long long int key) {
  int f = loopflag;
  aflcrash(INV(low, mid, high, item, key), loopflag);
  if (f == 0 && loopflag == 1) {
    fprintf(
        fptr,
        "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
        "low", temp_low, "mid", temp_mid, "high", temp_high, "item", temp_item,
        "key", temp_key);
    fprintf(fptr,
            "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "low", low, "mid", mid, "high", high, "item", item, "key", key);

    assert(0);
  }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, low, mid, high, item, key)                 \
  \ 
{                                                                           \
    \ 
    int f = postflag;                                                          \
    \ 
   aflcrash(cond, postflag);                                                   \
    \ 
    if (f == 0 && postflag == 1) {                                             \
      \ 
        fprintf(                                                               \
          fptr,                                                                \
          "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "low",                                                                        \
          low, "mid", mid, "high", high, "item", item, "key", key);            \
      assert(0);                                                               \
    \ 
}                                                                         \
  }

int main() {
  // variable declarations
  int low;
  int high;
  int mid;
  long long int item;
  int SIZE;
  int key;

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

    long long int choices = buf[len - 1];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100,
             "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "low",
             low, "mid", mid, "high", high, "item", item, "key", key);

    // pre-conditions
    item = arr[buf[1]];
    high = buf[2];
    SIZE = (int)(sizeof(arr) / sizeof(arr[0]));
    low = buf[4];
    key = -1;
    mid = (low + high) >> 1;

    // fprintf(fptr, "%d, %d, %d, %d, %d\n", low, mid, high, key, choices);
    // precheck
    // loopcond : (low < high)
    if (choices > 90) {
      // pre-conditions
      low = 0;
      mid = 0;
      item = 0;
      key = -1;
      high = (int)(sizeof(arr) / sizeof(arr[0]));
      SIZE = (int)(sizeof(arr) / sizeof(arr[0]));
      // pre-conditions
      assume((preflag == 0));
      precount++;
      precheck(fptr, vars, low, mid, high, item, key);
    } else {
      // loop-check program
      assume((loopflag + postflag < 2));
      assume(INV(low, mid, high, item, key));

      // Loop Condition
      if (low < high) {
        // Bounded Unrolling
        int unroll = UNROLL_LIMIT;

        while ((low < high) && unroll--) {
          assume((loopflag == 0));

          int temp_low = low;
          int temp_mid = mid;
          int temp_high = high;
          int temp_item = item;
          int temp_key = key;

          // loop body
          mid = (low + high) >> 1;
          if ((item < arr[mid])) {
            high = mid;
          } else if ((item > arr[mid])) {
            low = mid + 1;
          } else {
            key = mid;
            break;
          }

          loopcount++;
          loopcheck(fptr, vars, temp_low, temp_mid, temp_high, temp_item,
                    temp_key, low, mid, high, item, key);
        }
      } else {
        // post-check program
        assume((postflag == 0));
        // post-condition
        // printf("%d", arr[mid]);
        postcount++;
        postcheck(fptr, vars,
                  (((arr[key] == item) && (key == mid)) || (key == -1)), low,
                  mid, high, item, key)
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