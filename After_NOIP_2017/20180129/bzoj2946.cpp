#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=4e3+1e2;

int ch[maxn][26],fa[maxn],len[maxn],f[maxn][5],deg[maxn],root,last,cnt,ans;
int n;

inline int NewNode(int ll) {
	len[++cnt] = ll;
	return cnt;
}
inline void extend(int x) {
	int p = last;
	int np = NewNode(len[p]+1);
	while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
	if( !p ) fa[np] = root;
	else {
		int q = ch[p][x];
		if( len[q] == len[p] + 1 ) fa[np] = q;
		else {
			int nq = NewNode(len[p]+1);
			memcpy(ch[nq],ch[q],sizeof(ch[q]));
			fa[nq] = fa[q] , fa[q] = fa[np] = nq;
			while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
		}
	}
	last = np;
}
inline void pir(char* s,int li,int id) {
	int now = root , plen = 0;
	for(int i=1;i<=li;i++) {
		const int t = s[i] - 'a';
		if( ch[now][t] ) now = ch[now][t] , ++plen;
		else {
			while( now && !ch[now][t] ) now = fa[now];
			if( !now ) now = root , plen = 0;
			else plen = len[now] + 1 , now = ch[now][t];
		}
		if( now != root ) f[now][id] = max( f[now][id] , plen );
	}
}
inline void topo() {
	for(int i=1;i<=cnt;i++) if( fa[i] ) ++deg[fa[i]];
	queue<int> q;
	for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
	while( q.size() ) {
		const int pos = q.front(); q.pop();
		if( pos == root ) break;
		int t = len[pos];
		for(int i=1;i<n;i++) t = min( t , f[pos][i] );
		ans = max( ans , t );
		for(int i=1;i<n;i++) f[fa[pos]][i] = max( f[fa[pos]][i] , f[pos][i] );
		if( !--deg[fa[pos]] ) q.push(fa[pos]);
	}
}

int main() {
	static char in[maxn];
	static int li;
	scanf("%d",&n);
	scanf("%s",in+1) , li = strlen(in+1);
	root = last = NewNode(0);
	for(int i=1;i<=li;i++)
		extend(in[i]-'a');
	int i;
	for(i=1;i<n;i++) {
		scanf("%s",in+1) , li = strlen(in+1);
		pir(in,li,i);
	}
	topo();
	printf("%d\n",ans);
	return 0;
}
