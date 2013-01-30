#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include "wregexp.h"

struct wregexp_prog_s
{
    int flags;
    wchar_t ch;
};

    wregexp_prog_t *
wregexp_prog_compile(
        const wchar_t *pattern,
        int *err)
{
    size_t len;
    int result = WREGEXP_OK;
    wregexp_prog_t *prog = NULL;
    wregexp_prog_t *end = NULL;
    wregexp_prog_t *p = NULL;

    /* Check pattern length. */
    len = wcslen(pattern);
    if (len >= INT_MAX)
    {
        result = WREGEXP_TOOLONG;
        goto END;
    }
    /* Allocate memory for regexp program. */
    prog = calloc(sizeof(*prog), len + 1);
    if (prog == NULL)
    {
        result = WREGEXP_LOWMEM;
        goto END;
    }
    /* Initialize regexp program. */
    end = prog + len;
    for (p = prog; p < end; ++p)
    {
        p->flags = 0;
        p->ch = *pattern;
        ++pattern;
    }
    end->flags = 1;
    end->ch = L'\0';
END:
    if (err != NULL)
        *err = result;
    return prog;
}

    void
wregexp_prog_free(
        wregexp_prog_t *prog)
{
    if (prog != NULL)
        free(prog);
}

    int
wregexp_prog_match(
        wregexp_prog_t *prog,
        const wchar_t *text,
        wregexp_match_t *match)
{
    /* TODO */
    return 0;
}

    int
wregexp_match2(
        const wchar_t *pattern,
        const wchar_t *text,
        wregexp_match_t *match)
{
    int retval = -1;
    int err = 0;
    wregexp_prog_t *prog;

    prog = wregexp_prog_compile(pattern, &err);
    if (prog != NULL && err != 0)
        retval = wregexp_prog_match(prog, text, match);
    wregexp_prog_free(prog);
    return retval;
}

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
