#pragma once
//Task 1
int euclid(int a, int b);
int euclid_recurcive(int a, int b);
int euclid_binary(int a, int b);

//Task 2
int mod_pow(long long x, long long y, long long m);
int mod_pow_recurcive(int x, long y, int m);

//Task 3
int extented_euclid(int a, int b, int* x, int* y);
int mul_inverse(int x, int m);

//Task 4
int linear_diophantine(const int* a, int* x, int n, int b);

//Task 5
int chinese_reminder_iter(const int a[], const int m[], int k);
int chinese_reminder(const int a[], const int m[], int k);
//Task 5*
int chinese_reminder_general(const int a[], const int m[], int k);

//Task 6
int legendre_modpow(long long a, long long p);
int legendre_euclid_2(long long a, long long p);
int legendre_euclid(long long a, long long p);

//Task 7
int quadric_residue(int a, int p);