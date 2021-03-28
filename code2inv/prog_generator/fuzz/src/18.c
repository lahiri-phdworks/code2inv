#include <18.h>
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

#define INV(x, m, n) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int x, int m, int n)
{
    int f = preflag;
    aflcrash(INV(x, m, n), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n",
                "x", x, "m", m, "n", n);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int x, int m, int n)
{
    int f = loopflag;
    aflcrash(INV(x, m, n), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n",
                "x", x, "m", m, "n", n);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, x, m, n)   \
    \ 
{                             \
        \ 
    int f = postflag;              \
        \ 
   aflcrash(cond, postflag);       \
        \ 
    if (f == 0 && postflag == 1)   \
        {                          \
            \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n",\ 
 "x",                              \
               x, "m", m, "n", n); \
            fflush(stderr);        \
        \ 
}                         \
    }

int main()
{
    int x;
    int m;
    int n;

    freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int8_t *buf;

        HF_ITER(&buf, &len);

        int choices = buf[0];
        x = buf[1];
        n = buf[2];

        // pre-conditions
        assume((-10000 <= n && n < 10000));
        // precheck
        // loopcond : (x < n)

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            (x = 1);
            (m = 1);
            precheck(x, m, n);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, m, n));

            // Loop Condition
            if ((x < n))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((x < n) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    {
                        if (choices > 60)
                        {
                            m = x;
                        }
                        x = x + 1;
                    }
                    loopcheck(x, m, n);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                if (n > 1)
                {
                    postcheck((m >= 1), x, m, n)
                }
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}