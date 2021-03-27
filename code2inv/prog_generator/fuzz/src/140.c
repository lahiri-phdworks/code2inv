#include <140.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 10

#define aflcrash(cond, flag) \
    if (!cond)               \
        flag = 1;

#define assume(cond) \
    if (!cond)       \
        continue;

#define INV(sum, n, i, y, i2) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int sum, int n, int i, int y, int i2)
{
    int f = preflag;
    aflcrash(INV(sum, n, i, y, i2), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int sum, int n, int i, int y, int i2)
{
    int f = loopflag;
    aflcrash(INV(sum, n, i, y, i2), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, sum, n, i, y, i2)              \
    \ 
{                                                 \
        \ 
    int f = postflag;                                  \
        \ 
   aflcrash(cond, postflag);                           \
        \ 
    if (f == 0 && postflag == 1)                       \
        {                                              \
            \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "sum",                                                \
               sum, "n", n, "i", i, "y", y, "i2", i2); \
            fflush(stderr);                            \
        \ 
}                                             \
    }

int main()
{
    // variable declarations
    int sum;
    int n;
    int i;
    int y;
    int i2;
    freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int8_t *buf;

        HF_ITER(&buf, &len);

        int choices = buf[0];

        // pre-conditions
        n = buf[1];
        assume((n > 0));
        assume((n < 500000));
        // precheck
        // loopcond : (i <= n)

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            (sum = 0);
            (i = 1);
            (i2 = 0);
            precheck(sum, n, i, y, i2);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(sum, n, i, y, i2));

            // Loop Condition
            if ((i <= n))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((i <= n) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    {
                        (i2 = i * i);
                        (i = i + 1);
                        (y = (i * (i + 1) * (2 * i + 1) / 6));
                        sum = sum + i2;
                    }
                    loopcheck(sum, n, i, y, i2);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcheck((sum == (n * (n + 1) * (2 * n + 1) / 6)), sum, n, i, y, i2)
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}