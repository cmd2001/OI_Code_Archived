#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=3e2+1e1;

int in[2][maxn<<1],cur;
int n;

inline int mid(int a,int b,int c) {
	static int now[3];
	now[0] = a , now[1] = b , now[2] = c;
	sort(now,now+3);
	return now[1];
}
inline void trans(int* dst,int* sou,int l,int r) {
	for(int i=1;i<=n<<1;i++)
		dst[i] = 0;
	for(int i=l+1;i+1<=r;i++)
		dst[i] = mid(sou[i-1],sou[i],sou[i+1]);
}
inline int getans() {
	int l = 1 , r = ( n<<1 ) - 1;
	while( l != r ) {
		trans(in[cur^1],in[cur],l,r);
		++l , --r , cur^=1;
	}
	return in[cur][l];
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<n<<1;i++)
		scanf("%d",in[cur]+i);
	printf("%d\n",getans());
	return 0;
}
