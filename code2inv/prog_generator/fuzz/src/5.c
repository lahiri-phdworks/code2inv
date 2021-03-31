#include <5.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/file.h>
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

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int x, long long int size, long long int y, long long int z)
{
   int f = preflag;
   aflcrash(INV(x, size, y, z), preflag);
   if (f == 0 && preflag == 1)
   {
      fprintf(file_descp, "Pre : %s\n",
              buff);
   }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int x, long long int size, long long int y, long long int z)
{
   int f = loopflag;
   aflcrash(INV(x, size, y, z), loopflag);
   if (f == 0 && loopflag == 1)
   {
      fprintf(file_descp, "Loop : %s\n",
              buff);
   }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, size, y, z) \
   \ 
{                                                    \
      \ 
    int f = postflag;                                    \
      \ 
   aflcrash(cond, postflag);                             \
      \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(file_descp, "Post : %s\n", buff); \ 
}     \
   }

int main()
{
   int x = 0;
   long long int size;
   long long int y;
   long long int z;

   char buff[1024];
   memset(buff, '\0', sizeof(buff));

   FILE *fptr = fopen("models.txt", "w");
   setvbuf(fptr, buff, _IOLBF, 1024);

   for (;;)
   {
      size_t len;
      const int32_t *buf;

      HF_ITER(&buf, &len);

      long long int choices = buf[0];
      size = buf[1];
      y = buf[2];
      z = buf[3];

      char vars[128];
      memset(vars, '\0', sizeof(vars));
      snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld", "x", x, "size", size, "y", y, "z", z);

      // pre-conditions
      assume((-10000 <= size && size <= 10000));
      // precheck
      // loopcond : (x < size)

      if (choices > 25)
      {
         //pre-conditions
         assume((preflag == 0));
         precount++;
         precheck(fptr, vars, x, size, y, z);
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
               loopcount++;
               loopcheck(fptr, vars, x, size, y, z);
            }
         }
         else
         {
            // post-check program
            assume((postflag == 0));
            // post-condition
            if (size > 0)
            {
               {
                  postcount++;
                  postcheck(fptr, vars, z >= y, x, size, y, z)
               }
            }
         }
      }

      if (preflag + loopflag + postflag == 0 && counter == 100)
      {
         fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount", loopcount, "postcount", postcount);
         counter = 0;
      }

      if (preflag + loopflag + postflag >= 3)
         assert(0);
   }
}