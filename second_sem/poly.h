#pragma once

typedef struct poly {
    int coeff;
    int exp;
    struct poly* next;
} poly;

poly* poly_get(const char* input);
void poly_free(poly *p);
void poly_print(poly *p);

poly* poly_add(poly* p1, poly* p2);
poly* poly_multy(poly* p1, poly* p2);
