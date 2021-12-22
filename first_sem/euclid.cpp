#include <iostream>
#include "euclid.h"

//Task 1.
int euclid(int a, int b)
{
	while ((a != 0) && (b != 0))
	{
		if (a > b) a = a % b;
		else b = b % a;
	}
	return a + b;
}
int euclid_recurcive(int a, int b)
{
	if ((a == 0) || (b == 0)) return (a + b);
	return euclid_recurcive(b % a, a);
}
int euclid_binary(int a, int b)
{
	int k = 0;
	if ((a == 0) || (b == 0)) return a + b;
	if (a == b) return a;
	while (a != b)
	{
		while (((a & 1) == 0) & ((b & 1) == 0))
		{
			a = a >> 1;
			b = b >> 1;
			k++;
		}
		if ((a & 1) == 0) a >>= 1;
		if ((b & 1) == 0) b >>= 1;
		if (a > b) a = a - b;
		if (b > a) b = b - a;
	}
	return a << k;
}

//Task 2. 
int mod_pow(long long x, long long y, long long m)
{
	long long answ = 1;
	while (y != 0)
	{
		if (y & 1)
		{
			answ = (answ * x) % m;
		}
		x = (x * x) % m;
		y >>= 1;
	}
	return answ % m;
}
int mod_pow_recurcive(int x, long y, int m)
{
	if (y == 0) return 1 % m;
	if (y == 1) return x % m;
	int semi_result = mod_pow_recurcive(x, y >> 2, m);
	semi_result *= semi_result;
	if (y & 1) {
		semi_result *= x;
	}
	semi_result %= m;
	return semi_result;
}

//Task 3. 
int extented_euclid(int a, int b, int* x, int* y)
{
	int x_, y_;
	x_ = 1; y_ = 1;
	if (a == 0) {
		*x = 0; *y = 1; return b;
	}
	int c = extented_euclid(b % a, a, &x_, &y_);
	*x = y_ - (b / a) * x_;
	*y = x_;
	return c;
}
int mul_inverse(int x, int m)
{
	int x_, y;
	if ((extented_euclid(x, m, &x_, &y)) > 1) { return 0; }
	else
	{
		if (x_ > 0) return x_;
		else return m + x_;
	}
}

//Task 4.
int linear_diophantine(const int* a, int* x, int n, int b)
{
	if (n == 0) return -1;
	if (n == 1) {
		if (b % *a == 0) { *x = b / *a; return 0; }
		else return -1;
	}

	int gcd = extented_euclid(a[0], a[1], x, x + 1);
	for (int i = 2; i < n; ++i) {
		int t;
		gcd = extented_euclid(gcd, *(a + i), &t, x + i);
		for (int j = 0; j < i; j++)*(x + j) *= t;
	}
	if (b % gcd != 0) return -1;
	if (gcd == b) return 0;
	b /= gcd;
	for (int i = 0; i < n; i++)*(x + i) *= b;
	return 0;
}

//Task 5.
int chinese_reminder_iter(const int a[], const int m[], int k)
{
	int M = m[0];
	int x = a[0];
	for (int i = 0; i < k - 1; ++i) {
		int a1, b1, t;
		t = extented_euclid(M, m[i + 1], &a1, &b1);
		if (t != 1) return -1;
		x = a[i + 1] * M * a1 + x * m[i + 1] * b1;
		M *= m[i + 1];
		x %= (M);
	}
	if (x < 0) x = M + x;
	return x;
}
int chinese_reminder(const int a[], const int m[], int k)
{
	int M = m[0];
	int x = 0;
	for (int i = 1; i < k; ++i) {
		int t = euclid(M, m[i]);
		M *= m[i];
		if (t != 1) return -1;
	}
	for (int i = 0; i < k; ++i) {
		int M_ = (M / m[i]);
		x += (a[i] * M_ * mul_inverse(M_, m[i]));
	}
	return (x % M);
}
//Task 5*
int chinese_reminder_general(const int a[], const int m[], int k)
{
	//НОД(m[i],m[j]) | a[i]-a[j] - решение существует
	int M = m[0];
	int x = a[0];
	for (int i = 0; i < k - 1; ++i) {
		for (int j = i + 1; j < k; j++)
			if ((a[i] - a[j]) % euclid(m[i], m[j]) != 0) return -1;
		int a1, b1, t;
		t = extented_euclid(M, m[i + 1], &a1, &b1);
		if (t != 1)
			x = (a[i + 1] * M * a1 + x * m[i + 1] * b1);
		M *= m[i + 1];
		x %= (M);
		int gcd = euclid(x, M);
		x /= gcd;
		M /= gcd;
	}
	if (x < 0) x = M + x;
	return x;
}

//Task 6.
int legendre_modpow(long long a, long long p)
{
	if (a % p == 0) return 0;
	if ((mod_pow(a, (p - 1) / 2, p) == 1)) return 1;
	return -1;
}
int legendre_euclid_2(long long a, long long p)
{
	if (a % p == 0) return 0;
	int sign = 1;
	while (a > 2)
	{
		long long two = ((p * p - 1) / 8);
		while ((a & 1) == 0) {
			if ((two & 1) == 1) sign *= -1;
			a >>= 1;
		}
		long long t = a;
		a = p % t;
		p = t;
		if (((a & 3) == 3) && ((p & 3) == 3)) sign *= -1;
	}
	return sign;
}
int legendre_euclid(long long a, long long p)
{
	if (a % p == 0) return 0;
	int sign = 1;
	while (a > 2)
	{
		int k = 0;
		while ((a & 1) == 0) {
			k++;
			a >>= 1;
		}
		if ((k & 1) && (((p & 7) == 3) || ((p & 7) == 5))) sign *= -1;
		long long t = a;
		a = p % t;
		p = t;
		if (((a & 3) == 3) && ((p & 3) == 3)) sign *= -1;
	}
	return sign;
}

//Task 7.
int quadric_residue(int a, int p)
{
	if (legendre_modpow(a, p) == 1)
	{
		int c = 2, k = 0, b = 1, h = p - 1;
		while (legendre_modpow(c, p) == 1)
			c++;
		while ((h & 1) == 0) {
			k++;
			h >>= 1;
		}
		int r = k - int(k >= 2);
		while (r > 0) {
			int i = 0;
			while ((mod_pow(a, (1 << i) * h, p) * mod_pow(b, 1 << (i + 1), p)) != 1) {
				++i;
			}
			r = i;
			b = (b * mod_pow(c, h * (1 << (k - r - 1)), p)) % p;
			r--;
		}
		int x = (mod_pow(a, (h + 1) / 2, p) * b) % p;
		return x;
	}
	return -1;
}