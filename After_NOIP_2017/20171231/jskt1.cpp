#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
#define debug cout
using namespace std;
const int maxn=4e5+1e2;
const int inf=0x3f3f3f3f;

struct Node {
    map<int,Node*> ch;
    Node* fa;
    int len,deg,mir,mxr;
    Node() {
        mir = inf , mxr = -inf;
    }
}ns[maxn],*root,*last;

int in[maxn>>1];
int n,m,cnt,ans;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}

inline void extend(int x,int rr) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
    np->mir = np->mxr = rr;
    while( p && p->ch.find(x) == p->ch.end() )
        p->ch[x] = np,
        p = p->fa;
    if( !p )
        np->fa = root;
    else {
        //debug<<"in else 1"<<endl;
        Node* q = p->ch[x];
        if( q->len == p->len + 1 )
            np->fa = q;
        else {
            //debug<<"in else"<<endl;
            Node* nq = NewNode(p->len+1);
            nq->fa = q->fa;
            nq->ch = q->ch;
            np->fa = q->fa = nq;
            while( p && p->ch[x] == q )
                p->ch[x] = nq,
                p = p->fa;
        }
    }
    last = np;
}

inline void topo() {
    ans = -1;
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
        ans = max( ans , min( pos->len , pos->mxr - pos->mir - 1 ) );
        //debug<<"len = "<<pos->len<<"deltar = "<<pos->mxr-pos->mir<<endl;
        pos->fa->mxr = max( pos->fa->mxr , pos->mxr );
        pos->fa->mir = min( pos->fa->mir , pos->mir );
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    
    last = root = NewNode(0);
    for(int i=2;i<=n;i++)
        extend(in[i]-in[i-1],i-1);
    topo();
    
    printf("%d\n",ans+1);
    
    return 0;
}
