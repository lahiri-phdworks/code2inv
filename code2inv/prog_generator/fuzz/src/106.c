#include <106.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/file.h>
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

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int a, long long int m, long long int j, long long int k)
{
    int f = preflag;
    aflcrash(INV(a, m, j, k), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(file_descp, "Pre : %s\n",
                buff);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int a, long long int m, long long int j, long long int k)
{
    int f = loopflag;
    aflcrash(INV(a, m, j, k), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(file_descp, "Loop : %s\n",
                buff);
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, a, m, j, k) \
    \ 
{                                                \
        \ 
    int f = postflag;                                 \
        \ 
   aflcrash(cond, postflag);                          \
        \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(file_descp, "Post : %s\n", buff); \ 
}  \
    }

int main()
{
    // variable declarations
    long long int a, m, j, k;

    char buff[1024];
    memset(buff, '\0', sizeof(buff));

    FILE *fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 1024);

    for (;;)
    {
        size_t len;
        const int32_t *buf;

        HF_ITER(&buf, &len);

        long long int choices = buf[0];
        m = buf[1];
        a = buf[2];

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld", "a", a, "m", m, "j", j, "k", k);

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
            precount++;
            precheck(fptr, vars, a, m, j, k);
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
                    loopcount++;
                    loopcheck(fptr, vars, a, m, j, k);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                {
                    postcount++;
                    postcheck(fptr, vars, a >= m, a, m, j, k)
                }
            }
        }

        if (preflag + loopflag + postflag == 0 && counter == 100)
        {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount", loopcount, "postcount", postcount);
            counter = 0;
        }

        if (preflag + loopflag + postflag >= 3)
            assert(0);
    }
}