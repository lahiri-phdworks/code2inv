#include <22.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 128

#define aflcrash(cond, flag) \
    if (!cond)               \
        flag = 1;

#define assume(cond) \
    if (!cond)       \
        continue;

#define INV(z1, z2, z3, x, m, n) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int z1, long long int z2, long long int z3, long long int x, long long int m, long long int n)
{
    int f = preflag;
    aflcrash(INV(z1, z2, z3, x, m, n), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "z1", z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);
        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_x, long long int temp_m, long long int temp_n,
               long long int z1, long long int z2, long long int z3, long long int x, long long int m, long long int n)
{
    int f = loopflag;
    aflcrash(INV(z1, z2, z3, x, m, n), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "z1", z1, "z2", z2, "z3", z3, "x", temp_x, "m", temp_m, "n", temp_n);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "z1", z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);
        assert(0);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, z1, z2, z3, x, m, n)         \
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
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "z1",                                                           \
                z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n); \
            assert(0);                                           \
        \ 
}                                                       \
    }

long long int func(long long int a, long long int b)
{
    return a + b;
}

int main()
{
    long long int z1, z2, z3;
    long long int x;
    long long int m;
    long long int n;

    char buff[1024];
    memset(buff, '\0', sizeof(buff));

    FILE *fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 1024);

    // freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const int16_t *buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];
        x = buf[1];
        m = buf[2];
        n = buf[3];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "z1", z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);

        // pre-conditions
        // precheck
        // loopcond : (x < n)

        if (choices > 10000)
        {
            //pre-conditions
            assume((preflag == 0));
            (x = 1);
            (m = 1);
            precount++;
            precheck(fptr, vars, z1, z2, z3, x, m, n);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(z1, z2, z3, x, m, n));

            // Loop Condition
            if ((x < n))
            {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((x < n) && unroll--)
                {
                    assume((loopflag == 0));
                    long long int temp_x = x;
                    long long int temp_m = m;
                    long long int temp_n = n;
                    {
                        // loop body
                        if (choices > 1500)
                        {
                            m = x;
                        }
                        x = func(x, 1);
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_m, temp_n, z1, z2, z3, x, m, n);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if (n > 1)
                {
                    //assert (m < n);
                    postcount++;
                    postcheck(fptr, vars, (m >= 1), z1, z2, z3, x, m, n)
                }
            }
        }

        if (preflag + loopflag + postflag == 0 && counter == 100)
        {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n",
                    "precount", precount, "loopcount", loopcount, "postcount", postcount);
            counter = 0;
        }

        if (preflag + loopflag + postflag >= 3)
        {
            fclose(fptr);
            assert(0);
        }
    }

    fclose(fptr);
    return 0;
}