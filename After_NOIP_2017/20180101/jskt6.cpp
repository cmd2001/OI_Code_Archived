#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

char in[maxn>>1];
int k,cnt,li;
lli ans;

struct Node {
	Node *fa,*ch[26];
	int len,deg;
	lli lazy,sizr;
}ns[maxn],*root,*last;

inline Node* NewNode(int ll) {
	ns[++cnt].len = ll;
	return ns+cnt;
}

inline void extend(int x) {
	Node* p = last;
	Node* np = NewNode(p->len+1);
	np->sizr = 1;
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

inline void pre() {
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
		pos->fa->sizr += pos->sizr;
		if( !--pos->fa->deg )
			q.push(pos->fa);
	}
}

inline void getans() {
	int len = 0;
	Node* now = root;
	for(int i=1;i<=li;i++) {
		int t = in[i] - 'a';
		if( now->ch[t] ) {
			++len;
			now = now->ch[t];
		}
		else {
			while( now && !now->ch[t] )
				now = now->fa;
			if( !now ) {
				now = root;
				len = 0;
			}
			else {
				len = now->len + 1;
				now = now->ch[t];
			}
		}
		if( now == root ) // remember this or you will get a segmentation fault
			continue;
		// len can't more than pos->len!
		if( len >= max( k , now->fa->len + 1 ) )
			ans += now->sizr * ( len - max( k , now->fa->len + 1 ) + 1 );
		if( len >= now->fa->len )
			++now->fa->lazy;
	}
}

inline void topo() {
	for(int i=1;i<=cnt;i++)
		ns[i].deg = 0;
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
		if( pos->len >= max( k , pos->fa->len + 1 ) )
			ans += pos->sizr * pos->lazy * ( pos->len - max( k , pos->fa->len + 1 ) + 1 );
		pos->fa->lazy += pos->lazy;
		if( !--pos->fa->deg )
			q.push(pos->fa);
	}
}

int main() {
	scanf("%d",&k);
	scanf("%s",in+1);
	li = strlen(in+1);
	
	last = root = NewNode(0);
	for(int i=1;i<=li;i++)
		extend(in[i]-'a');
	//debug<<"cnt = "<<cnt<<endl;
	
	scanf("%s",in+1);
	li = strlen(in+1);
	
	pre();
	//debug<<"pred"<<endl;
	getans();
	//debug<<"ans got"<<endl;
	topo();
	
	printf("%lld\n",ans);
	
	return 0;
}
