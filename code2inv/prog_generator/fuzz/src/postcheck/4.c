#include <4.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond) \
   if (!cond)          \
      assert(0);

#define assume(cond) \
   if (!cond)        \
      exit(0);

#define INV(x, y, z) PHI

// COMMENT : precheck template
void precheck(int x, int y, int z)
{
   char buffer[30];
   fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n", "x", x, "y", y, "z", z);
   aflcrash(INV(x, y, z));
}
// COMMENT : loopcheck template
void loopcheck(int x, int y, int z)
{
   char buffer[30];
   fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n", "x", x, "y", y, "z", z);
   aflcrash(INV(x, y, z));
}
// COMMENT : postcheck template
void post(int x, int y, int z)
{
   char buffer[30];
   fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n", "x", x, "y", y, "z", z);
   aflcrash(INV(x, y, z));
}

int main()
{
   int x = 0;
   int y, z;

   while (x < 500)
   {
      x += 1;
      if (z <= y)
      {
         y = z;
      }
   }

   assert(z >= y);
}
