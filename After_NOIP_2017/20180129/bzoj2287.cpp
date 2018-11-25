#include<cstdio>
#include<cstring>
const int maxn=2e3+1e1;

int in[maxn],f[maxn],t[maxn];
int n,m;

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",in+i);
	f[0] = 1;
	for(int i=1;i<=n;i++)
		for(int j=m;j>=in[i];j--)
			f[j] = ( f[j] + f[j-in[i]] ) % 10;
	for(int i=1;i<=n;i++) {
		memcpy(t,f,sizeof(f));
		for(int j=in[i];j<=m;j++)
			t[j] = ( t[j] - t[j-in[i]] + 10 ) % 10;
		for(int j=1;j<=m;j++)
			putchar('0'+t[j]);
		putchar('\n');
	}
	return 0;
}
