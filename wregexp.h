#ifndef WREGEXP_H
#define WREGEXP_H

#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    WREGEXP_OK = 0,
    WREGEXP_TOOLONG = 1,
    WREGEXP_LOWMEM = 2
};

typedef struct wregexp_prog_s wregexp_prog_t;

typedef struct wregexp_match_s {
    const wchar_t *start;
    const wchar_t *end;
} wregexp_match_t;

wregexp_prog_t *wregexp_prog_compile(
        const wchar_t *pattern,
        int *err);

void wregexp_prog_free(
        wregexp_prog_t *prog);

int wregexp_prog_match(
        wregexp_prog_t *prog,
        const wchar_t *text,
        wregexp_match_t *match);

int wregexp_match2(
        const wchar_t *pattern,
        const wchar_t *text,
        wregexp_match_t *match);

int wregexp_match(
        const wchar_t *pattern,
        const wchar_t *text,
        wregexp_match_t *match);

#ifdef __cplusplus
}
#endif

#endif/*WREGEXP_H*/
