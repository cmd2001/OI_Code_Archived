#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

char in[maxn>>1];
int sa[maxn>>1],rnk[maxn>>1],height[maxn>>1];
lli sum[maxn>>1];
int cc[maxn];
int kk,li;

namespace SAM {
	int ch[maxn][26],rc[maxn][26],fa[maxn],len[maxn],id[maxn],cnt,last,root;
	int stk[maxn],top,sal;
	inline int NewNode(int ll) {
		len[++cnt] = ll;
		return cnt;
	}
	inline void extend(int x,int iid) {
		int p = last;
		int np = NewNode(len[p]+1);
		id[np] = iid;
		while( p && !ch[p][x] )
			ch[p][x] = np,
			p = fa[p];
		if( !p )
			fa[np] = root;
		else {
			int q = ch[p][x];
			if( len[q] == len[p] + 1 )
				fa[np] = q;
			else {
				int nq = NewNode(len[p]+1);
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq] = fa[q];
				fa[q] = fa[np] = nq;
				while( p && ch[p][x] == q )
					ch[p][x] = nq,
					p = fa[p];
			}
		}
		last = np;
	}
	
	inline void pre(int pos) {
		for(int i=0;i<26;i++)
			if( ch[pos][i] && len[ch[pos][i]] == len[pos] + 1 ) {
				const int &x = ch[pos][i];
				stk[++top] = i;
				rc[fa[x]][stk[len[x]-len[fa[x]]]] = x;
				pre(x);
				stk[top--] = '\0';
			}
	}
	
	inline void dfs(int pos) {
		if( id[pos] )
			sa[++sal] = id[pos];
		for(int i=0;i<26;i++)
			if( rc[pos][i] )
				dfs(rc[pos][i]);
	}
	
	inline void calh() {
		for(int i=1;i<=li;i++)
			rnk[sa[i]] = i;
		for(int i=1,k=0;i<=li;i++) {
			const int p1 = i , p2 = sa[rnk[i]-1];
			if( k )
				k--;
			while( p1+k <= li && p2+k <= li && in[p1+k] == in[p2+k] )
				++k;
			height[rnk[i]] = k;
		}
	}
	
	inline void work() {
		last = root = NewNode(0);
		for(int i=li;i;i--)
			extend(in[i]-'a',i);
		pre(root);
		dfs(root);
		calh();
	}
}

inline void kth_str(lli k,int &l,int &r,int* pp=NULL) {
	l = r = 0;
	int pos = lower_bound(sum+1,sum+1+li,k) - sum;
	l = sa[pos];
	r = sa[pos] + k - sum[pos-1] + height[pos] - 1; // different substrings including in[sa[pos]+height[pos]].
	if(pp)
		*pp = pos;
}

inline bool judge(lli k) {
	int l,r,pos,ret=0;
	kth_str(k,l,r,&pos);
	int len = r - l + 1;
	
	memset(cc,-1,sizeof(cc));
	cc[sa[pos]] = len;
	
	for(int i=pos+1;i<=li;i++) {
		len = min( len , height[i] );
		if( !len )
			return 0;
		cc[sa[i]] = len;
	}
	
	for(int i=1,last=li+1;i<=li;i++) {
		if( i == last ) {
			if( ++ret >= k )
				return 0;
			last = li + 1;
		}
		if( ~cc[i] )
			last = min( last , i + cc[i] );
	}
	return ret < kk;
}

inline void getans() {
	lli l = 1 , r = sum[li] , mid;
	while( r > l + 1 ) {
		mid = ( l + r ) >> 1;
		//debug<<"mid = "<<mid<<endl;
		if( judge(mid) ) {
			r = mid;
			//debug<<"r = mid"<<endl;
		}
		else
			l = mid;
	}
	
	//debug<<"ans = "<<r<<endl;
	int sl,sr;
	kth_str(r,sl,sr);
	for(int i=sl;i<=sr;i++)
		putchar(in[i]);
	putchar('\n');
}

inline void getsum() {
	for(int i=1;i<=li;i++)
		sum[i] = li - ( sa[i] - 1 ) - height[i];
	for(int i=1;i<=li;i++)
		sum[i] += sum[i-1];
}

inline void printsa() {
	for(int i=1;i<=li;i++)
		debug<<sa[i]<<" ";debug<<endl;
	for(int i=1;i<=li;i++)
		debug<<height[i]<<" ";debug<<endl;
}

int main() {
	//freopen("dat.txt","r",stdin);
	//freopen("my.txt","w",stdout);
	scanf("%d%s",&kk,in+1);
	li = strlen(in+1);
	
	SAM::work();
	getsum();
	getans();
	//debug<<judge(6)<<endl;
	
	return 0;
}
