#include <5.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond) \
   if (!cond)          \
      assert(0);

// Guide AFL to proper values
// exit(0) is not a crash
#define assume(cond) \
   if (!cond)        \
      exit(0);

#define INV(x, size, y, z) PHI

// TODO : Automate generation of this snippet
void precheck(int x, int size, int y, int z)
{
   char buffer[30];
   fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "size", size, "y", y, "z", z);
   aflcrash(INV(x, size, y, z));
}

// TODO : Automate generation of this snippet
void loopcheck(int x, int size, int y, int z)
{
   char buffer[30];
   fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "size", size, "y", y, "z", z);
   aflcrash(INV(x, size, y, z));
}

// TODO : Automate generation of this snippet
void postcheck(int x, int size, int y, int z)
{
   char buffer[30];
   fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "size", size, "y", y, "z", z);
   aflcrash(INV(x, size, y, z));
}

int main()
{

   freopen("loopmodels.txt", "w", stderr);

   int x;
   int size;
   int y;
   int z;

   (x = 0);
   scanf("%d", &size);
   assume((-10000 <= size && size <= 10000));

   assume((INV(x, size, y, z)));
   assume((x < size));
   x += 1;
   if (z <= y)
   {
      y = z;
   }
   loopcheck(x, size, y, z);
}
