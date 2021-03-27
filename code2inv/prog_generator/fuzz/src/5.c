#include <5.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 10

#define aflcrash(cond, flag) \
   if (!cond)                \
      flag = 1;

#define assume(cond) \
   if (!cond)        \
      continue;

#define INV(x, size, y, z) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int x, int size, int y, int z)
{
   int f = preflag;
   aflcrash(INV(x, size, y, z), preflag);
   if (f == 0 && preflag == 1)
   {
      fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n",
              "x", x, "size", size, "y", y, "z", z);
      fflush(stderr);
   }
}

// COMMENT : Loopcheck template
void loopcheck(int x, int size, int y, int z)
{
   int f = loopflag;
   aflcrash(INV(x, size, y, z), loopflag);
   if (f == 0 && loopflag == 1)
   {
      fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n",
              "x", x, "size", size, "y", y, "z", z);
      fflush(stderr);
   }
}

// COMMENT : Postcheck template
#define postcheck(cond, x, size, y, z)           \
   \ 
{                                            \
      \ 
    int f = postflag;                            \
      \ 
   aflcrash(cond, postflag);                     \
      \ 
    if (f == 0 && postflag == 1)                 \
      {                                          \
         \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "x",                                            \
               x, "size", size, "y", y, "z", z); \
         fflush(stderr);                         \
      \ 
}                                         \
   }

int main()
{
   int x = 0;
   int size;
   int y;
   int z;
   freopen("models.txt", "w", stderr);

   for (;;)
   {
      size_t len;
      const int8_t *buf;

      HF_ITER(&buf, &len);

      int choices = buf[0];

      // pre-conditions
      size = buf[1];
      assume((-10000 <= size && size <= 10000));
      // precheck
      // loopcond : (x < size)

      if (choices > 25)
      {
         //pre-conditions
         assume((preflag == 0));
         precheck(x, size, y, z);
      }
      else
      {
         // loop-check program
         assume((loopflag + postflag < 2));
         assume(INV(x, size, y, z));

         // Loop Condition
         if ((x < size))
         {
            // Bounded Unrolling
            int k = UNROLL_LIMIT;
            while ((x < size) && k--)
            {
               assume((loopflag == 0));
               // loop body
               {
                  x += 1;
                  if (z <= y)
                  {
                     y = z;
                  }
               }
               loopcheck(x, size, y, z);
            }
         }
         else
         {
            // post-check program
            assume((postflag == 0));
            // post-condition
            if (size > 0)
            {
               postcheck(z >= y, x, size, y, z)
            }
         }
      }

      if (preflag + loopflag + postflag >= 3)
         assert(0);
   }
}