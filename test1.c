#include <stdio.h>

#include "wregexp.h"

#define ASSERT(expr) \
    do { if (!(expr)) { \
        printf("failed at file %s line %d: %s\n", __FILE__, __LINE__, #expr); \
        return 1; \
    } } while (0)

    int
main(int argc, char **argv)
{
    int r;
    wregexp_match_t m;
    const wchar_t *t;

    t = L"abababc";
    r = wregexp_match(L"abc", t, &m);
    ASSERT(r == 1);
    ASSERT(m.start == t + 4);
    ASSERT(m.end == t + 7);

    t = L"ababcab";
    r = wregexp_match(L"abc", t, &m);
    ASSERT(r == 1);
    ASSERT(m.start == t + 2);
    ASSERT(m.end == t + 5);

    return 0;
}
