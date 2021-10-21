int mod_pow(long long x, long long y, long long m)
{
	long answ = 1;
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
	int semi_result = mod_pow_recurcive(x, y / 2, m);
	semi_result *= semi_result;
	if (y & 1) {
		semi_result *= x;
	}
	semi_result %= m;
	return semi_result;
}
