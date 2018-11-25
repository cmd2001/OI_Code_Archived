#include<cstdio>
#include<algorithm>
#include<map>
#define lli long long int
using namespace std;
const int maxn=6e3+1e2,lim=1e9,maxl=20;

map<int,int> rec;
int ls[maxn],len;
lli f[maxn][maxl][10]; // f[multi][len][first]

inline void gen() {
	for(lli i=1;i<=lim;i*=2)
		for(lli j=i;j<=lim;j*=3)
			for(lli k=j;k<=lim;k*=5)
				for(lli l=k;l<=lim;l*=7)
					ls[++len] = l;
	sort(ls+1,ls+1+len);
	for(int i=1;i<=len;i++)
		rec[ls[i]] = i;
}
inline void pre() {
	for(int i=1;i<10;i++) {
		f[rec[i]][1][i] = 1;
	}
	for(int plen=1;plen<18;plen++)
		for(int mul=1;mul<=len;mul++)
			for(int lst=1;lst<10;lst++) {
				if( !f[mul][plen][lst] ) continue;
				for(int nw=1;nw<10;nw++) {
					const lli tar = ( (lli) ls[mul] ) * nw;
					if( tar > lim ) continue;
					f[rec[tar]][plen+1][nw] += f[mul][plen][lst];
				}
			}
}
inline lli core_calc(lli x,int mul) { 
	static int nums[maxl],cnt; cnt = 0;
	lli ret = 0;
	while( x ) nums[++cnt] = x % 10 , x /= 10;
	for(int i=1;i<cnt;i++)
		for(int j=1;j<10;j++)
			ret += f[mul][i][j];
	for(int i=cnt;i;i--) {
		for(int j=1;j<nums[i];j++) {
			ret += f[mul][i][j];
		}
		mul = ls[mul];
		if( ( !nums[i] )  || ( mul % nums[i] ) ) break;
		mul = rec[ mul / nums[i] ];
	}
	return ret;
}
inline lli calc(lli x,int imul) {
	lli ret = 0;
	int mul = lower_bound(ls+1,ls+1+len,imul) - ls;
	if( ls[mul] > imul ) --mul;
	for(int i=1;i<=mul;i++)
		ret += core_calc(x,i);
	return ret;
}

int main() {
	static lli l,r;
	static int n;
	gen();
	pre();
	scanf("%d%lld%lld",&n,&l,&r);
	printf("%lld\n",calc(r,n)-calc(l,n));
	return 0;
}
