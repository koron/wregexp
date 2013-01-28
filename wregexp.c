#include "wregexp.h"

    int
wregexp_match(
        const wchar_t *pattern,
        const wchar_t *text,
        wregexp_match_t *match)
{
    wregexp_match_t m = { NULL, NULL };
    const wchar_t *t = text;
    const wchar_t *t0;
    const wchar_t *p = pattern;

    t0 = t;
    while (1)
    {
        if (*p == L'\0')
        {
            m.start = t0;
            m.end = t;
            break;
        }
        else if (*t == L'\0')
            break;
        else if (*t != *p)
        {
            t = ++t0;
            p = pattern;
        }
        else
        {
            ++t;
            ++p;
        }
    }

    if (match != NULL) {
        *match = m;
    }
    return m.start != NULL ? 1 : 0;
}
