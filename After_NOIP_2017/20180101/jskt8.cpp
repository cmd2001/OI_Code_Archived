#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=4e3+1e2;

char in[maxn>>1];
int n,len,cnt,ans;

struct Node {
    Node *fa,*ch[26];
    int len,deg,f[110];
}ns[maxn],*last,*root;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}

inline void extend(int x) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
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
			q->fa = np->fa = nq;
			while( p && p->ch[x] == q )
				p->ch[x] = nq,
				p = p->fa;
		}
	}
	last = np;
}

inline void pir(char* sou,int l,int id) {
	Node* now = root;
	int len = 0;
	for(int i=1;i<=l;i++) {
		const int t = sou[i] - 'a';
		if( now->ch[t] ) {
			++len,
			now = now->ch[t];
		}
		else {
			while( now && !now->ch[t] )
				now = now->fa;
			if( !now )
				now = root , len = 0;
			else
				len = now->len + 1,
				now = now->ch[t];
		}
		now->f[id] = max( now->f[id] , len );
	}
}

inline void topo() {
	for(int i=1;i<=cnt;i++)
		if( ns[i].fa )
			++ns[i].fa->deg;
	queue<Node*> q;
	for(int i=1;i<=cnt;i++)
		if( !ns[i].deg )
			q.push(ns+i);
	while( q.size() ) {
		const Node* pos = q.front(); q.pop();
		if( pos == root )
			break;
		int mxl = pos->len;
		for(int i=1;i<n;i++)
			mxl = min( mxl , pos->f[i] );
		ans = max( ans , mxl );
		for(int i=1;i<n;i++)
			pos->fa->f[i] = max( pos->fa->f[i] , pos->f[i] );
		if( !--pos->fa->deg )
			q.push(pos->fa);
	}
}

int main() {
	scanf("%d",&n);
	scanf("%s",in+1);
	len = strlen(in+1);
	if( n == 1 ) {
		printf("%d\n",len);
		return 0;
	}
	
	last = root = NewNode(0);
	for(int i=1;i<=len;i++)
		extend(in[i]-'a');
	
	for(int i=1;i<n;i++) {
		scanf("%s",in+1);
		len = strlen(in+1);
		pir(in,len,i);
		reverse(in+1,in+1+len); // right ] ?
		pir(in,len,i);
	}
	
	topo();
	
	printf("%d\n",ans);
	
	return 0;
}
