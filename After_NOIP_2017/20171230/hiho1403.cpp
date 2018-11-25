#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=4e4+1e2;

int n,m,cnt,ans;
int in[maxn];

struct Node {
	Node* par,*nxt[100];
	int len;
	long long deg,tme;
}ns[maxn],*root,*last;

Node* NewNode(int ll) {
	ns[++cnt].len = ll;
	return &ns[cnt];
}

inline void extend(int x) {
	Node* p = last;
	Node* np = NewNode(p->len+1);
	np -> tme = 1;
	while( p && !p->nxt[x] )
		p->nxt[x] = np,
		p = p->par;
	if( !p )
		np->par = root;
	else {
		Node* q = p->nxt[x];
		if( q->len == p->len + 1 )
			np->par = q;
		else {
			Node* nq = NewNode(p->len+1);
			memcpy(nq->nxt,q->nxt,sizeof(q->nxt));
			nq->par = q->par;
			q->par = np->par = nq; // ?
			while( p && p->nxt[x] == q )
				p->nxt[x] = nq,
				p = p->par;
		}
	}
	last = np;
}

inline void topo() {
	for(int i=1;i<=cnt;i++)
		if( ns[i].par )
			++ns[i].par->deg;
	queue<Node*> q;
	for(int i=1;i<=cnt;i++)
		if( !ns[i].deg )
			q.push(ns+i);
	while( q.size() ) {
		const Node* pos = q.front(); q.pop();
		if( pos == root )
			break;
		if( pos->tme >= m ) {
			ans = max( ans , pos->len );
		}
        //debug<<"len = "<<pos->len<<"tme = "<<pos->tme<<endl;
		pos->par->tme += pos->tme;
		if( !--pos->par->deg )
			q.push(pos->par);
	}
}

int main() {
	last = root = NewNode(0);
	root->tme = 0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",in+i);
	for(int i=1;i<=n;i++)
		extend(in[i]-1);
	
	topo();
    //debug<<"cnt = "<<cnt<<endl;
	
	printf("%d\n",ans);
	
	return 0;
}
