#include <109.h>
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

#define INV(a, c, m, j, k) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int a, int c, int m, int j, int k)
{
    int f = preflag;
    aflcrash(INV(a, c, m, j, k), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "a", a, "c", c, "m", m, "j", j, "k", k);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int a, int c, int m, int j, int k)
{
    int f = loopflag;
    aflcrash(INV(a, c, m, j, k), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "a", a, "c", c, "m", m, "j", j, "k", k);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, a, c, m, j, k)             \
    \ 
{                                             \
        \ 
    int f = postflag;                              \
        \ 
   aflcrash(cond, postflag);                       \
        \ 
    if (f == 0 && postflag == 1)                   \
        {                                          \
            \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "a",                                              \
               a, "c", c, "m", m, "j", j, "k", k); \
            fflush(stderr);                        \
        \ 
}                                         \
    }

int main()
{
    // variable declarations
    int a;
    int c;
    int m;
    int j;
    int k;
    freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int8_t *buf;

        HF_ITER(&buf, &len);

        int choices = buf[0];

        // pre-conditions
        a = buf[1];
        c = buf[2];
        m = buf[3];
        // precheck
        // loopcond : (k < c)

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            (j = 0);
            (k = 0);
            precheck(a, c, m, j, k);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(a, c, m, j, k));

            // Loop Condition
            if ((k < c))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((k < c) && k--)
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
                    loopcheck(a, c, m, j, k);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if (c > 0)
                {
                    postcheck((a <= m), a, c, m, j, k)
                }
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}