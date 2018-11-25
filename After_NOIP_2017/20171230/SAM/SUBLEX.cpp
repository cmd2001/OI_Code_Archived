#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

char in[maxn];
int len,m,cnt;

struct Node {
	Node *fa,*fm,*nxt[26];
	int len;
	lli sum;
}ns[maxn],*root,*last;

inline Node* NewNode(int ll) {
	ns[++cnt].len = ll;
	return &ns[cnt];
}

inline void extend(int x) {
	Node* p = last;
	Node* np = NewNode(p->len+1);
	while( p && !p->nxt[x] )
		p->nxt[x] = np,
		p = p->fa;
	if( !p )
		np->fa = root;
	else {
		Node* q = p->nxt[x];
		if( q->len == p->len + 1 )
			np->fa = q;
		else {
			Node* nq = NewNode(p->len+1);
			memcpy(nq->nxt,q->nxt,sizeof(q->nxt));
			nq->fa = q->fa;
			np->fa = q->fa = nq;
			while( p && p->nxt[x] == q )
				p->nxt[x] = nq,
				p = p->fa;
		}
	}
	last = np;
}

inline lli dfs(Node* pos) {
	if( pos->sum )
		return pos->sum;
	lli ret = 0;
	for(int i=0;i<26;i++)
		if( pos->nxt[i] )
			ret += dfs(pos->nxt[i]);
	pos->sum = ret + ( pos != root );
	return pos->sum;
}

inline void query(lli x) {
	Node* pos = root;
	while( x ) {
		for(int i=0;i<26;i++)
			if( pos->nxt[i] ) {
				if( x <= pos->nxt[i]->sum ) {
					putchar(i+'a');
					pos = pos -> nxt[i];
					--x;
					break;
				}
				else
					x -= pos->nxt[i]->sum;
			}
	}
	putchar('\n');
}

int main() {
	scanf("%s",in+1);
	len = strlen(in+1);
	
	last = root = NewNode(0);
	for(int i=1;i<=len;i++)
		extend(in[i]-'a');
	
	dfs(root);
	
	scanf("%d",&m);
	while( m-- ) {
		lli x;
		scanf("%lld",&x);
		query(x);
	}
	
	return 0;
}

