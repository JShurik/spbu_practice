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
