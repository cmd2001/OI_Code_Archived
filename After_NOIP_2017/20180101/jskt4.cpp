#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e3+1e2;
const int inf=0x3f3f3f3f;

char in[maxn];
int cnt,li;
long long ans;

struct Node {
	Node *fa,*ch[26];
	int len,deg,mir,mxr;
	Node() {
		mir = inf , mxr = -inf;
	}
}ns[maxn],*last,*root;

Node* NewNode(int ll) {
	ns[++cnt].len = ll;
	return ns+cnt;
}

inline void extend(int x,int pos) {
	Node* p = last;
	Node* np = NewNode(p->len+1);
	np->mir = np->mxr = pos;
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
		if( min( pos->len , pos->mxr - pos->mir) > pos->fa->len ) {
			ans += min( pos->len , pos->mxr - pos->mir) - pos->fa->len;
		}
		pos->fa->mir = min( pos->fa->mir , pos->mir );
		pos->fa->mxr = max( pos->fa->mxr , pos->mxr );
		if( !--pos->fa->deg )
			q.push(pos->fa);
	}
}

int main() {
	scanf("%s",in+1);
	li = strlen(in+1);
	
	last = root = NewNode(0);
	for(int i=1;i<=li;i++)
		extend(in[i]-'a',i);
	//debug<<"extended"<<endl;
	
	topo();
	printf("%lld\n",ans);
	
	return 0;
}
