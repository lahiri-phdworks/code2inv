#include <132.h>
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

#define INV(i, j, c, t) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int i, long long int j, long long int c, long long int t)
{
    int f = preflag;
    aflcrash(INV(i, j, c, t), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(file_descp, "Pre : %s\n",
                buff);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int i, long long int j, long long int c, long long int t)
{
    int f = loopflag;
    aflcrash(INV(i, j, c, t), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(file_descp, "Loop : %s\n",
                buff);
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, i, j, c, t) \
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
    long long int i = 0;
    long long int j, c, t;

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
        t = buf[1];
        j = buf[2];
        c = buf[3];

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld", "i", i, "j", j, "c", c, "t", t);

        // pre-conditions
        // precheck
        // loopcond : (unknown())

        if (choices > 25)
        {
            //pre-conditions
            assume((preflag == 0));
            precount++;
            precheck(fptr, vars, i, j, c, t);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, j, c, t));

            // Loop Condition
            if ((choices > 55))
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((choices > 55) && k--)
                {
                    assume((loopflag == 0));
                    {
                        if (c > 48)
                        {
                            if (c < 57)
                            {
                                j = i + i;
                                t = c - 48;
                                i = j + t;
                            }
                        }
                    }
                    loopcount++;
                    loopcheck(fptr, vars, i, j, c, t);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                {
                    postcount++;
                    postcheck(fptr, vars, i >= 0, i, j, c, t)
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
            assert(0);
    }
}