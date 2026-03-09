struct pointer_with_type {
    void *ptr;
    char type;
};
typedef struct pointer_with_type PWT;

struct listelem {
    PWT content;
    struct listelem *next;
};
typedef struct listelem * list;

list cons(PWT content, list tail);
void lprint(list l);

list map(list l, PWT (*f) (PWT) );

list take_abs(list numlist);
list take_strlen(list strlist);

PWT foldl(list l, PWT initval, PWT (*agg)(PWT, PWT) );
PWT foldr(list l, PWT initval, PWT (*agg)(PWT, PWT) );

long len(list l);
long sum(list numlist);
long totlen(list strlist);
char *cat(list strlist);

list rev(list l);

