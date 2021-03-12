#include <132.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond) \
    if (!cond)         \
        assert(0);

// Guide AFL to proper values
// exit(0) is not a crash
#define assume(cond) \
    if (!cond)       \
        exit(0);

#define INV(i, j, c, t) PHI

// TODO : Automate generation of this snippet
void precheck(int i, int j, int c, int t)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "c", c, "t", t);
    aflcrash(INV(i, j, c, t));
}

// TODO : Automate generation of this snippet
void loopcheck(int i, int j, int c, int t)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "c", c, "t", t);
    aflcrash(INV(i, j, c, t));
}

// TODO : Automate generation of this snippet
void postcheck(int i, int j, int c, int t)
{
    char buffer[30];
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "c", c, "t", t);
    aflcrash(INV(i, j, c, t));
}

int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};
int unknown()
{
    int nums = sizeof(choices) / sizeof(choices[0]);
    return choices[(rand() % nums) - 1];
}

int main()
{
    int i;
    int j;
    int c;
    int t;

    // pre-conditions
    (i = 0);
    scanf("%d", &c);

    assume((c >= 40 && c <= 60))
        precheck(i, j, c, t);

    while (unknown())
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
        loopcheck(i, j, c, t);
    }

    postcheck(i, j, c, t);
    // post-condition
    assert(i >= 0);
}
