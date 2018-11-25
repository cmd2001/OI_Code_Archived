#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
#define debug cout
using namespace std;
const int maxn=4e5+1e2;

struct Node {
    map<int,Node*> ch;
    Node* fa;
    int len,deg,sum;
}ns[maxn],*root,*last;

int in[maxn>>1],n,m,cnt,ans;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}
inline void extend(int x) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
    np->sum = 1;
    while( p && p->ch.find(x) == p->ch.end() )
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
            nq->fa = q->fa;
            nq->ch = q->ch;
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
        //debug<<"pos = "<<pos-ns<<endl;
        //debug<<"len = "<<pos->len<<"sum = "<<pos->sum<<endl;
        if( pos->sum >= m )
            ans = max( ans , pos->len );
        pos->fa->sum += pos->sum;
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    
    last = root = NewNode(0);
    
    for(int i=1;i<=n;i++)
        extend(in[i]);
    topo();
    
    //debug<<"cnt = "<<cnt<<endl;
    
    printf("%d\n",ans);
    
    return 0;
}