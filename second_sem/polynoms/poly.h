#pragma once

enum expt { E0, E1, E2, E3, E4 };

typedef struct exception {
    int pos;
    expt e;
} exeption;

typedef struct poly {
    int coeff;
    int exp;
    struct poly* next;
} poly;

void poly_free(poly* p);
void print_exeption(exeption* ex);
poly* poly_get_monomial(int coeff, int exp);

void poly_merge(poly** p1, poly* p2);
poly* poly_get(const char* input, exeption* e);
void poly_print(poly* p);
poly* poly_add(poly* p1, poly* p2);
poly* poly_multy(poly* p1, poly* p2);
