#pragma once

typedef struct big_int {
	int sgn;
	unsigned int length;
	unsigned char* number;
} big_int;

//general constuction
big_int* big_int_get(const char* num_bi);
void big_int_print(big_int* n);
void big_int_free(big_int* n);
void big_int_assign(big_int* n1, const big_int* n2);

//basic maths
big_int* big_int_change_sgn(const big_int* n);
int big_int_abs_compare(const big_int* n1, const big_int* n2);
big_int* big_int_add(const big_int* n1, const big_int* n2);
big_int* big_int_sub(const big_int* n1, const big_int* n2);
big_int* big_int_multi(const big_int* n1, const big_int* n2);
big_int* big_int_left_shift(const big_int* n1, int n2);
big_int* big_int_right_shift(const big_int* n1, int n2);
big_int* big_int_euclidean_division(const big_int* n1, const big_int* n2, big_int* r);


//algs
big_int* big_int_mod_pow(big_int* x, big_int* y, const big_int* p);
