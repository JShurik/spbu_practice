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
