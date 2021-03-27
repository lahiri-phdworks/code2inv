#include <106.h>
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

#define INV(a, m, j, k) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int a, int m, int j, int k)
{
    int f = preflag;
    aflcrash(INV(a, m, j, k), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n",
                "a", a, "m", m, "j", j, "k", k);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int a, int m, int j, int k)
{
    int f = loopflag;
    aflcrash(INV(a, m, j, k), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n",
                "a", a, "m", m, "j", j, "k", k);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, a, m, j, k)        \
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
 "a",                                      \
               a, "m", m, "j", j, "k", k); \
            fflush(stderr);                \
        \ 
}                                 \
    }

int main()
{
    // variable declarations
    int a, m, j, k;

    freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int8_t *buf;

        HF_ITER(&buf, &len);

        int choices = buf[0];
        m = buf[1];
        a = buf[2];
        // pre-conditions
        assume((-10000 <= m && m <= 10000));
        assume((-10000 <= a && a <= 10000));

        // precheck
        // loopcond : (k < 1)

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            assume(a <= m);
            assume(j < 1);
            (k = 0);
            precheck(a, m, j, k);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(a, m, j, k));

            // Loop Condition
            if ((k < 1))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((k < 1) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    {
                        if (m < a)
                        {
                            m = a;
                        }
                        k = k + 1;
                    }
                    loopcheck(a, m, j, k);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcheck(a >= m, a, m, j, k)
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}