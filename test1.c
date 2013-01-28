#include <stdio.h>

#include "wregexp.h"

#define ASSERT(expr)    do { \
    if (!(expr)) { printf("failed: %s\n", #expr); return 1; } \
} while (0)

    int
main(int argc, char **argv)
{
    {
        int r1;
        wregexp_match_t m1;
        wchar_t *t1 = L"abababc";

        r1 = wregexp_match(L"abc", t1, &m1);
        ASSERT(r1 == 1);
        ASSERT(m1.start == t1 + 4);
        ASSERT(m1.end == t1 + 7);
    }

    {
        int r2;
        wregexp_match_t m2;
        wchar_t *t2 = L"ababcab";

        r2 = wregexp_match(L"abc", t2, &m2);
        ASSERT(r2 == 1);
        ASSERT(m2.start == t2 + 2);
        ASSERT(m2.end == t2 + 5);
    }

    return 0;
}
