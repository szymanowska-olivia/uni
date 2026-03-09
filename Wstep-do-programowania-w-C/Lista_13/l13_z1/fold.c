#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fold.h"

list cons(PWT content, list tail) {
    if (tail && tail->content.type != content.type) return NULL;
    list new_elem = malloc(sizeof(struct listelem));
    if (!new_elem) return NULL;
    new_elem->content = content;
    new_elem->next = tail;
    return new_elem;
}

void lprint(list l) {
    while (l) {
        if (l->content.type == 'i')
            printf("%ld ", *(long *)l->content.ptr);
        else if (l->content.type == 's')
            printf("%s ", (char *)l->content.ptr);
        l = l->next;
    }
    printf("\n");
}

PWT abs_aux(PWT val) {
    if (val.type != 'i') return (PWT){NULL, 'n'};
    long *num = malloc(sizeof(long));
    if (!num) return (PWT){NULL, 'n'};
    *num = labs(*(long *)val.ptr);
    return (PWT){num, 'i'};
}

PWT strlen_aux(PWT val) {
    if (val.type != 's') return (PWT){NULL, 'n'};
    long *len = malloc(sizeof(long));
    if (!len) return (PWT){NULL, 'n'};
    *len = strlen((char *)val.ptr);
    return (PWT){len, 'i'};
}

list map(list l, PWT (*f)(PWT)) {
    if (!l) return NULL;
    PWT new_content = f(l->content);
    if (!new_content.ptr) return map(l->next, f);
    return cons(new_content, map(l->next, f));
}

list take_abs(list numlist) { return map(numlist, abs_aux); }
list take_strlen(list strlist) { return map(strlist, strlen_aux); }

PWT foldl(list l, PWT initval, PWT (*agg)(PWT, PWT)) {
    while (l) {
        initval = agg(initval, l->content);
        l = l->next;
    }
    return initval;
}

PWT foldr(list l, PWT initval, PWT (*agg)(PWT, PWT)) {
    if (!l) return initval;
    return agg(l->content, foldr(l->next, initval, agg));
}

PWT len_aux(PWT acc, PWT _) {
    (void)_; 
    long *count = malloc(sizeof(long));
    if (!count) return (PWT){NULL, 'n'};
    *count = *(long *)acc.ptr + 1;
    free(acc.ptr);
    return (PWT){count, 'i'};
}

long len(list l) {
    PWT init = {malloc(sizeof(long)), 'i'};
    if (!init.ptr) return 0;
    *(long *)init.ptr = 0;
    PWT result = foldl(l, init, len_aux);
    long res = *(long *)result.ptr;
    free(result.ptr);
    return res;
}

PWT sum_aux(PWT acc, PWT val) {
    if (acc.type != 'i' || val.type != 'i') return (PWT){NULL, 'n'};
    long *sum = malloc(sizeof(long));
    if (!sum) return (PWT){NULL, 'n'};
    *sum = *(long *)acc.ptr + *(long *)val.ptr;
    free(acc.ptr);
    return (PWT){sum, 'i'};
}

long sum(list numlist) {
    PWT init = {malloc(sizeof(long)), 'i'};
    if (!init.ptr) return 0;
    *(long *)init.ptr = 0;
    PWT result = foldl(numlist, init, sum_aux);
    long res = *(long *)result.ptr;
    free(result.ptr);
    return res;
}

PWT totlen_aux(PWT acc, PWT val) {
    if (acc.type != 'i' || val.type != 's') return (PWT){NULL, 'n'};
    long *total = malloc(sizeof(long));
    if (!total) return (PWT){NULL, 'n'};
    *total = *(long *)acc.ptr + strlen((char *)val.ptr);
    free(acc.ptr);
    return (PWT){total, 'i'};
}

long totlen(list strlist) {
    PWT init = {malloc(sizeof(long)), 'i'};
    if (!init.ptr) return 0;
    *(long *)init.ptr = 0;
    PWT result = foldl(strlist, init, totlen_aux);
    long res = *(long *)result.ptr;
    free(result.ptr);
    return res;
}

PWT cat_aux(PWT acc, PWT val) {
    if (acc.type != 's' || val.type != 's') return (PWT){NULL, 'n'};
    size_t len = strlen((char *)acc.ptr) + strlen((char *)val.ptr) + 1;
    char *new_str = malloc(len);
    if (!new_str) return (PWT){NULL, 'n'};
    strcpy(new_str, (char *)acc.ptr);
    strcat(new_str, (char *)val.ptr);
    free(acc.ptr);
    return (PWT){new_str, 's'};
}

char *cat(list strlist) {
    PWT init = {malloc(1), 's'};
    if (!init.ptr) return NULL;
    *(char *)init.ptr = '\0';
    PWT result = foldl(strlist, init, cat_aux);
    return (char *)result.ptr;
}

PWT cons_aux(PWT acc, PWT val) {
    if (val.ptr == NULL) return acc;
    return (PWT){ cons(val, (list)acc.ptr), 'l' };
}

list rev(list l) {
    PWT init = {NULL, 'l'};
    PWT result = foldl(l, init, cons_aux);
    return (list)result.ptr;
}
