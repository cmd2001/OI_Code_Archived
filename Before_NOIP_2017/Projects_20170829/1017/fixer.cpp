#include<bits/stdc++.h>
using namespace std;
const int maxn=(1e5);
char old[maxn],nwe[maxn];

int main()
{
	for(int i=1;i<=20;i++)
	{
		sprintf(old,"maximum%d.ans",i);
		sprintf(nwe,"maximum%d.out",i);
		rename(old,nwe);
	}
	return 0;
}

