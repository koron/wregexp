#ifndef WREGEXP_H
#define WREGEXP_H

#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wregexp_match_s {
    const wchar_t *start;
    const wchar_t *end;
} wregexp_match_t;

int wregexp_match(
        const wchar_t *pattern,
        const wchar_t *text,
        wregexp_match_t *match);

#ifdef __cplusplus
}
#endif

#endif/*WREGEXP_H*/
