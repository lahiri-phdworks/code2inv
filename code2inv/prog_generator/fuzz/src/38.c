#include <38.h>
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

#define INV(n, c) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int n, int c)
{
    int f = preflag;
    aflcrash(INV(n, c), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d\n",
                "n", n, "c", c);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int n, int c)
{
    int f = loopflag;
    aflcrash(INV(n, c), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d\n",
                "n", n, "c", c);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, n, c)    \
    \ 
{                           \
        \ 
    int f = postflag;            \
        \ 
   aflcrash(cond, postflag);     \
        \ 
    if (f == 0 && postflag == 1) \
        {                        \
            \ 
       fprintf(stderr, "Post : %s : %d, %s : %d\n",\ 
 "n",                            \
               n, "c", c);       \
            fflush(stderr);      \
        \ 
}                       \
    }

int main()
{
    // variable declarations
    int n;
    int c = 0;
    freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int8_t *buf;

        HF_ITER(&buf, &len);

        int choices = buf[0];

        // pre-conditions
        n = buf[1];
        assume(n > 0);
        // precheck
        // loopcond : (unknown())

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            precheck(n, c);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(n, c));

            // Loop Condition
            if ((unknown()))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((unknown()) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    {
                        if (c == n)
                        {
                            c = 1;
                        }
                        else
                        {
                            c = c + 1;
                        }
                    }
                    loopcheck(n, c);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if (c == n)
                {
                    postcheck((c <= n), n, c)
                }
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}