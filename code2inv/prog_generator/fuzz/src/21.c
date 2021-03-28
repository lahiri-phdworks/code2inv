#include <21.h>
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

#define INV(x, m, n, z1, z2, z3) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// COMMENT : Precheck template
void precheck(int x, int m, int n, int z1, int z2, int z3)
{
    int f = preflag;
    aflcrash(INV(x, m, n, z1, z2, z3), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "x", x, "m", m, "n", n, "z1", z1, "z2", z2, "z3", z3);
        fflush(stderr);
    }
}

// COMMENT : Loopcheck template
void loopcheck(int x, int m, int n, int z1, int z2, int z3)
{
    int f = loopflag;
    aflcrash(INV(x, m, n, z1, z2, z3), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",
                "x", x, "m", m, "n", n, "z1", z1, "z2", z2, "z3", z3);
        fflush(stderr);
    }
}

// COMMENT : Postcheck template
#define postcheck(cond, x, m, n, z1, z2, z3)                     \
    \ 
{                                                           \
        \ 
    int f = postflag;                                            \
        \ 
   aflcrash(cond, postflag);                                     \
        \ 
    if (f == 0 && postflag == 1)                                 \
        {                                                        \
            \ 
       fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n",\ 
 "x",                                                            \
               x, "m", m, "n", n, "z1", z1, "z2", z2, "z3", z3); \
            fflush(stderr);                                      \
        \ 
}                                                       \
    }

int main()
{
    // variable declarations
    int z1;
    int z2;
    int z3;
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

        // pre-conditions
        n = buf[1];
        x = buf[2];
        m = buf[3];
        assume((-10000 <= m && m <= 10000));
        assume((-10000 <= x && x <= 10000));
        assume((-10000 <= n && n <= 10000));
        // precheck
        // loopcond : (x < n)

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            (x = 1);
            (m = 1);
            precheck(x, m, n, z1, z2, z3);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, m, n, z1, z2, z3));

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
                    loopcheck(x, m, n, z1, z2, z3);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if (n > 1)
                {
                    postcheck(m < n, x, m, n, z1, z2, z3)
                }
            }
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}