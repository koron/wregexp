#include "wregexp.h"

    static int inline
is_pattern_end(const wchar_t *p)
{
    return *p == L'\0';
}

    static int inline
is_item_match(const wchar_t *p, const wchar_t *t)
{
    return *p == *t ? 1: 0;
}

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
        int r;
        if (is_pattern_end(p))
        {
            m.start = t0;
            m.end = t;
            break;
        }
        else if (*t == L'\0')
            break;
        if ((r = is_item_match(p, t)) > 0)
        {
            /* forward pattern and input text. */
            p += r;
            ++t;
        }
        else
        {
            /* reset pattern. */
            p = pattern;
            /* backtrack input text. */
            t = ++t0;
        }
    }

    if (match != NULL) {
        *match = m;
    }
    return m.start != NULL ? 1 : 0;
}
