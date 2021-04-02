#include <21.h>
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

#define INV(x, m, n, z1, z2, z3) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
double precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *file_descp, char *buff, long long int x, long long int m, long long int n, long long int z1, long long int z2, long long int z3)
{
    int f = preflag;
    aflcrash(INV(x, m, n, z1, z2, z3), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(file_descp, "Pre : %s\n",
                buff);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *file_descp, char *buff, long long int temp_x, long long int temp_m, long long int temp_n,
               long long int x, long long int m, long long int n, long long int z1, long long int z2, long long int z3)
{
    int f = loopflag;
    aflcrash(INV(x, m, n, z1, z2, z3), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n",
                "x", temp_x, "m", temp_m, "n", temp_n);
        fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n",
                "x", x, "m", m, "n", n);
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, m, n, z1, z2, z3) \
    \ 
{                                                         \
        \ 
    int f = postflag;                                          \
        \ 
   aflcrash(cond, postflag);                                   \
        \ 
    if (f == 0 && postflag == 1) {\ 
        fprintf(file_descp, "Post : %s\n", buff); \ 
}           \
    }

int main()
{
    // variable declarations
    long long int z1;
    long long int z2;
    long long int z3;
    long long int x;
    long long int m;
    long long int n;

    char buff[1024];
    memset(buff, '\0', sizeof(buff));

    FILE *fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 1024);

    for (;;)
    {
        size_t len;
        const int32_t *buf;

        HF_ITER(&buf, &len);

        long long int choices = buf[3];
        n = buf[2];
        x = buf[1];
        m = buf[4];

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld", "x", x, "m", m, "n", n, "z1", z1, "z2", z2, "z3", z3);

        // pre-conditions
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
            precount++;
            precheck(fptr, vars, x, m, n, z1, z2, z3);
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
                    long long int temp_x = x;
                    long long int temp_m = m;
                    long long int temp_n = n;
                    // loop body
                    {
                        if (choices > 64)
                        {
                            m = x;
                        }
                        x = x + 1;
                    }
                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_m, temp_n, x, m, n, z1, z2, z3);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if (n > 1)
                {
                    {
                        postcount++;
                        postcheck(fptr, vars, (m < n), x, m, n, z1, z2, z3)
                    }
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