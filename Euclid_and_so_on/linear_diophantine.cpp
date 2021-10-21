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
