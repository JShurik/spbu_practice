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
		int two = ((p * p - 1) / 8);
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
