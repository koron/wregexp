#include <stdio.h>

#include "wregexp.h"

#define ASSERT(expr)    do { \
    if (!(expr)) { printf("failed: %s\n", #expr); return 1; } \
} while (0);

    int
main(int argc, char **argv)
{
    int r;
    wregexp_match_t m;
    wchar_t *t1 = L"ababcabc";

    r = wregexp_match(L"abc", t1, &m);
    ASSERT(r == 1);
    ASSERT(m.start == t1 + 2);
    ASSERT(m.end == t1 + 5);

    return 0;
}
