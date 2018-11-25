#include<stdio.h>
#include<vector>
#define heng 0
#define shu 1
using std::vector;
long long jiecheng(long long a)
{
	long long ret = 1;
	for (int i = a;i > 0;i--)
	{
		ret *= i;
	}
	return ret;
}
int main()
{
	freopen ("count.in", "r", stdin);
	freopen ("count.out", "w", stdout);
	while (1)
	{
		int n;long long m;
		scanf("%d%lld", &n, &m);
		if (!n && !m) break;
		long long ans = 0;
		if (!(n % 2))
		{
			long long squarenum = n/2;
			ans = 1;
			for (int i = 0;i < squarenum;i++)
			{
				ans *= 5;
			}
			if (ans>2147483640) ans %= m;
			printf("%lld", ans % m);
		}
		else
		{
			long long onlylinenum = (n/2)+1;
			long long squarenum = n/2;
			long long numtoadd = 1;
			for (int i = 0;i < squarenum;i++)
			{
				for (int j = squarenum-i;j >= 0;j--)
				{
					numtoadd *= 4;
				}
				if (i == 0) numtoadd *= onlylinenum;
				else numtoadd *= 2;
			}
			if (ans>2147483640) ans %= m;
			numtoadd += squarenum*squarenum;
			if (ans>2147483640) ans %= m;
			printf("%lld", ans % m);
		}
	}
	fclose(stdout);
	return 0;
}
