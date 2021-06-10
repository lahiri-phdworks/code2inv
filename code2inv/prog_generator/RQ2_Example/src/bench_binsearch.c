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
    0,     0,     0,     7,     7,     13,    16,    18,    24,    25,    25,
    405,   688,   1095,  1370,  1429,  1845,  1879,  2261,  2540,  3024,  3099,
    3299,  3389,  3646,  3758,  4231,  5203,  6581,  6725,  6811,  6946,  6949,
    7102,  7236,  7618,  7717,  8030,  8093,  8101,  8416,  8924,  9055,  9074,
    9623,  10128, 10974, 11330, 11628, 12056, 12088, 12236, 12611, 12816, 12940,
    13045, 13073, 13384, 13552, 13569, 13838, 13940, 13959, 14070, 14129, 14423,
    14508, 14595, 14682, 14743, 14772, 14920, 15335, 15492, 15498, 15544, 15653,
    15956, 16460, 16471, 17647, 17659, 17787, 17988, 18039, 18156, 18194, 18549,
    18830, 18930, 18932, 18954, 18973, 19242, 20050, 20088, 20093, 20214, 20251,
    20295, 20351, 20356, 20595, 20623, 20872, 22166, 22260, 22462, 22823, 22918,
    22973, 23479, 23631, 23976, 24387, 25184, 25391, 25875, 25943, 26673, 26997,
    27085, 27255, 27409, 27660, 27768, 27862, 27948, 28617, 28975, 28986, 29067,
    29084, 29169, 29408, 29455, 29787, 29827, 29845, 30631, 30698, 31053, 31135,
    31176, 31561, 31902, 31931, 32257, 32352, 32436, 32539, 32843, 33172, 33323,
    33389, 33509, 33538, 33885, 34050, 34450, 34590, 34607, 34829, 35144, 35316,
    35357, 35426, 35451, 35466, 35847, 36535, 37099, 37299, 37571, 38769, 38966,
    39292, 39395, 39506, 39625, 40022, 40125, 40443, 40608, 40721, 41123, 41248,
    41574, 41809, 41874, 42001, 42292, 42619, 42706, 42760, 42867, 42883, 43161,
    43672, 43794, 43818, 44004, 44395, 44972, 45074, 45196, 45397, 45497, 46082,
    46145, 46641, 46656, 47053, 47068, 47076, 47152, 47195, 47326, 47335, 47371,
    47487, 47556, 47706, 47941, 48651, 48672, 49334, 49945, 50031, 50417, 50455,
    50628, 50878, 50938, 50958, 51147, 51243, 51612, 51658, 51813, 51897, 52021,
    52425, 52438, 52528, 52659, 52699, 52818, 53291, 53414, 53694, 53822, 53972,
    54146, 54264, 54482, 54499, 54526, 54721, 54958, 55110, 55169, 55513, 55878,
    56019, 56962, 57159, 57283, 57409, 57518, 57591, 57986, 58278, 58436, 59309,
    59570, 59903, 60110, 60240, 60430, 60766, 60807, 61046, 61088, 61121, 61209,
    61377, 61870, 62049, 62095, 62104, 62106, 62146, 62281, 62324, 62378, 62496,
    62827, 62940, 63015, 63397, 63522, 63740, 63878, 64168, 64767, 64827, 65201,
    65260, 65266};

#define INV(low, mid, high, item) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

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
  unsigned int low;
  unsigned int high;
  unsigned int mid;
  unsigned int SIZE;
  int item;

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

    long long int choices = buf[0];

    char vars[100];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "low",
             low, "mid", mid, "high", high, "item", item);

    // pre-conditions
    item = buf[3];
    high = buf[2];
    SIZE = (int)(sizeof(arr) / sizeof(arr[0]));
    low = buf[1];
    mid = buf[4];

    // precheck
    // loopcond : (low < high)
    if (choices > 100) {
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
          mid = (low + high) >> 1;
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