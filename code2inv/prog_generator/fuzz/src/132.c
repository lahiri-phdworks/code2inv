#include <132.h>
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

#define INV(i, j, c, t) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int i, int j, int c, int t)
{
    int f = preflag;
    aflcrash(INV(i, j, c, t), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n",
                "i", i, "j", j, "c", c, "t", t);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int i, int j, int c, int t)
{
    int f = loopflag;
    aflcrash(INV(i, j, c, t), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n",
                "i", i, "j", j, "c", c, "t", t);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, i, j, c, t)        \
    \ 
{                                     \
        \ 
    int f = postflag;                      \
        \ 
   aflcrash(cond, postflag);               \
        \ 
    if (f == 0 && postflag == 1)           \
        {                                  \
            \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "i",                                      \
               i, "j", j, "c", c, "t", t); \
            fflush(stderr);                \
        \ 
}                                 \
    }

int main()
{
    // variable declarations
    int i = 0;
    int j, c, t;
    freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int8_t *buf;

        HF_ITER(&buf, &len);

        int choices = buf[0];

        // pre-conditions
        i = buf[1];
        j = buf[2];
        c = buf[3];
        // precheck
        // loopcond : (unknown())

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            (i = 0);
            precheck(i, j, c, t);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, j, c, t));

            // Loop Condition
            if ((choices > 55))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((choices > 55) && k--)
                {
                    assume((loopflag == 0));
                    {
                        if (c > 48)
                        {
                            if (c < 57)
                            {
                                j = i + i;
                                t = c - 48;
                                i = j + t;
                            }
                        }
                    }
                    loopcheck(i, j, c, t);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcheck(i >= 0, i, j, c, t)
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}