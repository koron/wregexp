#include <assert.h>

#include "wregexp.h"

    static const wchar_t *
get_end(const wchar_t *p)
{
    return p + wcslen(p);
}

    static int inline
is_end(const wchar_t *p, const wchar_t *end)
{
    return p > end;
}

    static int inline
is_item_match(const wchar_t *p, const wchar_t *t, int *step)
{
    int r = 0, s = 0;
    wchar_t pch = *p;

    switch (pch)
    {
        case '.':
            if (*t != L'\0')
                s = 1, r = 1;
            break;

        case L'\0':
            s = 1, r = 1;
            break;

        default:
            if (pch == *t)
                s = 1, r = 1;
            break;
    }

    if (step != NULL)
        *step = s;
    return r;
}

    int
wregexp_match(
        const wchar_t *pattern,
        const wchar_t *text,
        wregexp_match_t *match)
{
    wregexp_match_t m = { NULL, NULL };
    const wchar_t *t = text;
    const wchar_t *t_end = get_end(t);
    const wchar_t *p = pattern;
    const wchar_t *p_end = get_end(p);
    const wchar_t *t0;

    t0 = t;
    while (1)
    {
        int step = 0;
        if (is_item_match(p, t, &step))
        {
            /* forward pattern and input text. */
            p += step;
            if (is_end(p, p_end))
            {
                m.start = t0;
                m.end = t;
                break;
            }
            ++t;
        }
        else
        {
            /* reset pattern. */
            p = pattern;
            /* backtrack input text. */
            t = ++t0;
        }
        if (is_end(t, t_end))
            break;
    }

    if (match != NULL) {
        *match = m;
    }
    return m.start != NULL ? 1 : 0;
}
