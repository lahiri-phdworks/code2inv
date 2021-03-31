#include <63.h>
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

#define INV(x, y) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int x, long long int y)
{
    int f = preflag;
    aflcrash(INV(x, y), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(file_descp, "Pre : %s\n",
                buff);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int x, long long int y)
{
    int f = loopflag;
    aflcrash(INV(x, y), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(file_descp, "Loop : %s\n",
                buff);
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, y)      \
    \ 
{                                               \
        \ 
    int f = postflag;                                \
        \ 
   aflcrash(cond, postflag);                         \
        \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(file_descp, "Post : %s\n", buff); \ 
} \
    }

int main()
{
    // variable declarations
    long long int x;
    long long int y;

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
        x = buf[1];

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld", "x", x, "y", y);

        // pre-conditions
        // precheck
        // loopcond : (x <= 10)

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            (x = 1);
            precount++;
            precheck(fptr, vars, x, y);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, y));

            // Loop Condition
            if ((x <= 10))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((x <= 10) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    {
                        y = 10 - x;
                        x = x + 1;
                    }
                    loopcount++;
                    loopcheck(fptr, vars, x, y);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                {
                    postcount++;
                    postcheck(fptr, vars, y >= 0, x, y)
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