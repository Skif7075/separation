#include "Calculations.h"

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	if (a == 0)
		return b;
	if (b > a)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
	int rem = a%b;
	while (rem>0)
	{
		a = b;
		b = rem;
		rem = a%b;
	}
	if (rem == 0)
		return b;
	else
		return rem;
}
int lcm(int n)
{
	if (n == 2)
		return 2;
	int *num = new int[n];
	for (int i = 0; i < n; i++)
		num[i] = i + 1;
	int lcm = num[1] * num[2] / gcd(num[1], num[2]);
	for (int i = 3; i < n; i++)
		lcm = lcm*num[i] / gcd(lcm, num[i]);
	return lcm;
}
int fact(int n)
{
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	return n*fact(n - 1);
}
int rec(int n, int k)
{
	if (n == k)
		return 1;
	if (k == 1)
		return n;
	return rec(n - 1, k - 1) + rec(n - 1, k);
}