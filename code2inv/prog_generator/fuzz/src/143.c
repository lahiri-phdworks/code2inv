#include <143.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>

#define UNROLL_LIMIT 512

#define aflcrash(cond, flag) \
    if (!cond)               \
        flag = 1;

#define assume(cond) \
    if (!cond)       \
        continue;

#define INV(q, d, n, r) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int q, long long int d, long long int n, long long int r)
{
    int f = preflag;
    aflcrash(INV(q, d, n, r), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "q", q, "d", d, "n", n, "r", r);
        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_q, long long int temp_d, long long int temp_n, long long int temp_r,
               long long int q, long long int d, long long int n, long long int r)
{
    int f = loopflag;
    aflcrash(INV(q, d, n, r), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "q", temp_q, "d", temp_d, "n", temp_n, "r", temp_r);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "q", q, "d", d, "n", n, "r", r);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, q, d, n, r) \
    \ 
{                                          \
        \ 
    int f = postflag;                           \
        \ 
   aflcrash(cond, postflag);                    \
        \ 
    if (f == 0 && postflag == 1)                \
        {                                       \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "q",                                           \
                q, "d", d, "n", n, "r", r);     \
            assert(0);                          \
        \ 
}                                      \
    }

int main()
{
    // variable declarations
    long long int q = 0;
    long long int d;
    long long int n;
    long long int r = n;

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
        n = buf[1];
        r = buf[2];
        d = buf[3];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "q", q, "d", d, "n", n, "r", r);

        // pre-conditions
        // precheck
        // loopcond : (r >= d)

        if (choices > 35000)
        {
            //pre-conditions
            assume((preflag == 0));
            (q = 0);
            (r = n);
            precount++;
            precheck(fptr, vars, q, d, n, r);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(q, d, n, r));

            // Loop Condition
            if ((r >= d))
            {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((r >= d) && unroll--)
                {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_r = r;
                    long long int temp_q = q;
                    long long int temp_d = d;
                    long long int temp_n = n;
                    {
                        // temp variables
                        r = r - d;
                        q = q + 1;
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_q, temp_d, temp_n, temp_r, q, d, n, r);
                }
            }
            else
            {
                if ((n >= 0))
                {
                    // post-check program
                    assume((postflag == 0));
                    // post-condition
                    postcount++;
                    postcheck(fptr, vars, ((r < d && n == q * d + r)), q, d, n, r)
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