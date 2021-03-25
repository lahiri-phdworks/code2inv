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

int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};
int unknown()
{
   int nums = sizeof(choices) / sizeof(choices[0]);
   return choices[(rand() % nums) - 1];
}

int main()
{
   // variable declarations
   int x = 0;
   int y;
   int z;

   scanf("%d", &y);
   scanf("%d", &z);
   freopen("loopmodels.txt", "w", stderr);

   // pre-conditions
   assume((-10000 <= y && y <= 10000));
   assume((-10000 <= z && z <= 10000));

   // loopcond : (x < 500)
   // loop-check program
   assume(INV(x, y, z));
   assume((x < 500));
   // loop body
   {
      x += 1;
      if (z <= y)
      {
         y = z;
      }
   }
   loopcheck(x, y, z);
}
