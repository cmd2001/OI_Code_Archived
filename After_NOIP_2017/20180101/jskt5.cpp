#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+1e2;

char in[maxn>>1];
int n,cnt,li,ans;

struct Node {
	Node *fa,*ch[26];
	int len;
}ns[maxn],*root,*last;

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

inline void getans() {
	int len = 0;
	Node* now = root;
	for(int i=1;i<=li;i++) {
		const int t = in[i] - 'a';
		if( now->ch[t] ) {
			++len;
			now = now->ch[t];
		}
		else {
			while( now && !now->ch[t] )
				now = now->fa;
			if( !now ) {
				len = 0;
				now = root;
			}
			else {
				len = now->len + 1;
				now = now->ch[t];
			}
		}
		ans = max( ans , len );
	}
}

int main() {
	scanf("%s",in+1);
	li = strlen(in+1);
	
	last = root = NewNode(0);
	for(int i=1;i<=li;i++)
		extend(in[i]-'a');
	//cout<<cnt<<endl;
	
	scanf("%s",in+1);
	li = strlen(in+1);
	
	getans();
	
	printf("%d\n",ans);
	
	return 0;
}
