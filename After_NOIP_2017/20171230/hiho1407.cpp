#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#define debug cout
using namespace std;
const int maxn=2.5e5+1e2;
const int inf=0x3f3f3f3f;

int in[maxn>>1];
int n,m,cnt,ans;

struct Node {
    Node *fa;
    map<int,Node*> nxt;
    int len,deg,mxr,mir;
    Node() {
        mxr = -inf , mir = inf;
    }
}ns[maxn],*root,*last;

Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}

inline void extend(int x,int pp) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
    np->mir = np->mxr = pp;
    while( p && p->nxt.find(x) == p->nxt.end() )
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
            nq->nxt = q->nxt; // ?
            nq->fa = q->fa;
            q->fa = np->fa = nq;
            while( p && p->nxt[x] == q )
                p->nxt[x] = nq,
                p = p->fa;
        }
    }
    last = np;
}

inline void topo() {
    for(int i=1;i<=cnt;i++)
        if( ns+i != root )
            ++ns[i].fa->deg;
    queue<Node*> q;
    for(int i=1;i<=cnt;i++)
        if( !ns[i].deg )
            q.push(ns+i);
    while( q.size() ) {
        const Node* pos = q.front(); q.pop();
        if( pos == root )
            break;
        ans = max( ans , min( pos->len , pos->mxr - pos->mir ) );
        pos->fa->mir = min( pos->fa->mir , pos->mir );  
        pos->fa->mxr = max( pos->fa->mxr , pos->mxr );
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    
    last = root = NewNode(0);
    for(int i=1;i<=n;i++)
        extend(in[i],i);
    topo();
    
    printf("%d\n",ans);
    
    return 0;
}


