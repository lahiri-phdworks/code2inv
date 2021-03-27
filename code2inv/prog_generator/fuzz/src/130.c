#include <130.h>
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

#define INV(d1, d2, d3, x1, x2, x3) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int d1, int d2, int d3, int x1, int x2, int x3)
{
    int f = preflag;
    aflcrash(INV(d1, d2, d3, x1, x2, x3), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int d1, int d2, int d3, int x1, int x2, int x3)
{
    int f = loopflag;
    aflcrash(INV(d1, d2, d3, x1, x2, x3), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, d1, d2, d3, x1, x2, x3)                       \
    \ 
{                                                                \
        \ 
    int f = postflag;                                                 \
        \ 
   aflcrash(cond, postflag);                                          \
        \ 
    if (f == 0 && postflag == 1)                                      \
        {                                                             \
            \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "d1",                                                                \
               d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3); \
            fflush(stderr);                                           \
        \ 
}                                                            \
    }

int main()
{
    // variable declarations
    int d1;
    int d2;
    int d3;
    int x1;
    int x2;
    int x3;

    freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int8_t *buf;

        HF_ITER(&buf, &len);

        int choices = buf[0];
        x2 = buf[1];
        x3 = buf[2];

        // pre-conditions
        assume((-10000 <= x2 && x1 <= 10000));
        assume((-10000 <= x3 && x3 <= 10000));
        // precheck
        // loopcond : (x1 > 0)

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            (d1 = 1);
            (d2 = 1);
            (d3 = 1);
            (x1 = 1);
            precheck(d1, d2, d3, x1, x2, x3);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(d1, d2, d3, x1, x2, x3));

            // Loop Condition
            if ((x1 > 0))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((x1 > 0) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    {
                        if (x2 > 0)
                        {
                            if (x3 > 0)
                            {
                                x1 = x1 - d1;
                                x2 = x2 - d2;
                                x3 = x3 - d3;
                            }
                        }
                    }
                    loopcheck(d1, d2, d3, x1, x2, x3);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcheck((x2 >= 0), d1, d2, d3, x1, x2, x3)
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}