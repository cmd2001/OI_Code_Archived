#include<cstdio>
#include<cctype>
const int maxn=6e3+1e2,maxe=5e4+1e2;
const int inf=0x3f3f3f3f;

int f[maxe],in[maxn][3],n,full,ans=inf;

inline int getint () {
	int ret = 0 , ch;
	while( !isdigit(ch=getchar()) );
	do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
	return ret;
}
inline int min(const int &a,const int &b) {
	return a < b ? a : b;
}
inline int max(const int &a,const int &b) {
	return a > b ? a : b;
}
int main() {
	n = getint();
	for(int i=1,t=inf;i<=n;i++,t=inf) {
		for(int j=0;j<3;j++) {
			in[i][j] = getint();
			if( !in[i][j] ) in[i][j] = inf;
			t = min(t,in[i][j]);
		}
		full += t;
	}
	for(int i=1;i<=n;i++)
		for(int j=full,t=inf;~j;j--,t=inf) {
			if( j - in[i][0] >= 0 ) t = min( t , f[j-in[i][0]] );
			t = min( t , f[j] + in[i][1] );
			if( j - in[i][2] >= 0 ) t = min( t , f[j-in[i][2]] + in[i][2] );
			f[j] = t;
		}
	for(int i=0;i<=full;i++) ans = min( ans , max(i,f[i]) );
	printf("%d\n",ans);
	return 0;
}
