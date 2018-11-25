#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

struct Node {
	Node *fa,*ch[26];
	int len,size,last,bel,sum;
}ns[maxn<<1],*root,*last,*t[maxn<<1];

char in[maxn];
lli ans[maxn];
int s[maxn],nxt[maxn<<1];
int n,m,li,cnt;

inline void addedge(int from,Node* to) {
	static int cnt = 0;
	t[++cnt] = to,
	nxt[cnt] = s[from] , s[from] = cnt;
}

inline Node* NewNode(int ll) {
	ns[++cnt].len = ll;
	return ns + cnt;
}

inline void extend(int x,int id) {
	//debug<<"x = "<<x<<"id = "<<id<<endl;
	Node* p = last;
	Node* np = NewNode(p->len+1);
	np->bel = id;
	while( p && !p->ch[x] )
		p->ch[x] = np,
		p = p->fa;
	if( !p )
		np->fa = root;
	else {
		Node* q = p->ch[x];
		if( q->len == p->len + 1 )
			np->fa = q;
		else {
			Node* nq = NewNode(p->len+1);
			memcpy(nq->ch,q->ch,sizeof(q->ch));
			nq->fa = q->fa;
			nq->size = q->size , nq->last = q->last;
			q->fa = np->fa = nq;
			while( p && p->ch[x] == q )
				p->ch[x] = nq,
				p = p->fa;
		}
	}
	p = np;
	while( p && p->last!=id ) {
		++p->size;
		p->last = id;
		p = p->fa;
	}
	last = np;
}

inline void dfs(Node* pos) {
	if( pos->fa )
		pos->sum += pos->fa->sum;
	if( pos->bel )
		ans[pos->bel] += pos->sum;
	for(int at=s[pos-ns];at;at=nxt[at])
		dfs(t[at]);
}

inline void pre() {
	for(int i=1;i<=cnt;i++) {
		if( ns[i].size >= m && ns[i].fa )
			ns[i].sum = ns[i].len - ns[i].fa->len;
		else
			ns[i].sum = 0;
		if( ns[i].fa )
			addedge(ns[i].fa-ns,ns+i);
	}
}

int main() {
	scanf("%d%d",&n,&m);
	
	last = root = NewNode(0);
	for(int i=1;i<=n;i++) {
		last = root;
		scanf("%s",in+1);
		li = strlen(in+1);
		for(int j=1;j<=li;j++)
			extend(in[j]-'a',i);
	}
	
	pre();
	dfs(root);
	
	for(int i=1;i<=n;i++) {
		printf("%lld",ans[i]);
		if( i != n )
			putchar(' ');
	}
	
	return 0;
}
