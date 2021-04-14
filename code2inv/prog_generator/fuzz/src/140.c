#include <140.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag) \
    if (!cond)               \
        flag = 1;

#define assume(cond) \
    if (!cond)       \
        continue;

#define INV(sum, n, i, y, i2) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int sum, long long int n, long long int i, long long int y, long long int i2)
{
    int f = preflag;
    aflcrash(INV(sum, n, i, y, i2), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_sum, long long int temp_n, long long int temp_i, long long int temp_y,
               long long int temp_i2, long long int sum, long long int n, long long int i, long long int y, long long int i2)
{
    int f = loopflag;
    aflcrash(INV(sum, n, i, y, i2), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "sum", temp_sum, "n", temp_n, "i", temp_i, "y", temp_y, "i2", temp_i2);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
        assert(0);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, sum, n, i, y, i2)   \
    \ 
{                                                  \
        \ 
    int f = postflag;                                   \
        \ 
   aflcrash(cond, postflag);                            \
        \ 
    if (f == 0 && postflag == 1)                        \
        {                                               \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "sum",                                                 \
                sum, "n", n, "i", i, "y", y, "i2", i2); \
            assert(0);                                  \
        \ 
}                                              \
    }
long long int foo(long long int sum, long long int i)
{
    return sum + (long long int)pow((double)i, (double)2);
}

int main()
{
    // variable declarations
    long long int sum;
    long long int n;
    long long int i;
    long long int y;
    long long int i2;

    char buff[1024];
    memset(buff, '\0', sizeof(buff));

    FILE *fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 1024);

    // freopen("models.txt", "w", stderr);

    for (;;)
    {
        size_t len;
        const uint16_t *buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];
        n = buf[1];
        i = buf[3];
        y = 0;
        i2 = 0;
        sum = buf[5];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "sum", sum, "n", n, "i", i, "y", y, "i2", i2);

        // pre-conditions
        // precheck
        // loopcond : (i <= n)

        if (choices > 15000)
        {
            //pre-conditions
            assume((preflag == 0));
            assume((n > 0));
            assume((n < 5000));
            (sum = 0);
            (i = 0);
            (i2 = 0);
            (y = 0);
            precount++;
            precheck(fptr, vars, sum, n, i, y, i2);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(sum, n, i, y, i2));

            // Loop Condition
            if ((i < n))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((i < n) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_sum = sum;
                    long long int temp_n = n;
                    long long int temp_i = i;
                    long long int temp_y = y;
                    long long int temp_i2 = i2;
                    {
                        i = i + 1;
                        // i2 = pow(i, 2);
                        // y = (i * (i + 1) * (2 * i + 1)) / (6);
                        sum = foo(sum, i);
                    }
                    // ( ( i <= n ) && ( sum == ( i * ( i + 1 ) * ( 2 * i + 1 )) / 6 ) )
                    loopcount++;
                    loopcheck(fptr, vars, temp_sum, temp_n, temp_i, temp_y, temp_i2, sum, n, i, y, i2);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, (sum == ((n * (n + 1) * (2 * n + 1)) / 6)), sum, n, i, y, i2)
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