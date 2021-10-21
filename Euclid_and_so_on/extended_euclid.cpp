int extended_euclid(int a, int b, int* x, int* y)
{
	int x_, y_;
	x_ = 1; y_ = 1;
	if (a == 0) {
		*x = 0; *y = 1; return b;
	}
	int c = extended_euclid(b % a, a, &x_, &y_);
	*x = y_ - (b / a) * x_;
	*y = x_;
	return c;
}

int mul_inverse(int x, int m)
{
	int x_, y;
	if ((extended_euclid(x, m, &x_, &y)) > 1) { return 0; }
	else
	{
		if (x_ > 0) return x_;
		else return m + x_;
	}
}
