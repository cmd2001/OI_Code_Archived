#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#define debug cout
using namespace std;
const int maxn=2e3+1e2;

struct Node {
    map<int,Node*> ch;
    Node *fa;
    int len,deg,f[maxn>>1];
}ns[maxn],*root,*last;

int in[maxn];
int li,cnt,ans;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns + cnt;
}
inline void extend(int x) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
    while( p && !p->ch.count(x) )
        p->ch[x] = np ,
        p = p->fa;
    if( !p )
        np->fa = root;
    else {
        Node* q = p->ch[x];
        if( q->len == p->len + 1 )
            np->fa = q;
        else {
            Node* nq = NewNode(p->len+1);
            nq->ch = q->ch;
            nq->fa = q->fa;
            q->fa = np->fa = nq;
            while( p && p->ch[x] == q )
                p->ch[x] = nq,
                p = p->fa;
        }
    }
    last = np;
}

inline void getans(int id) {
    Node* pos = root;
    int len = 0;
    for(int i=1;i<=li;i++) {
        const int t = in[i];
        if( pos->ch.count(t) ) {
            pos = pos->ch[t],
            ++len;
        }
        else {
            while( pos && !pos->ch.count(t) )
                pos = pos->fa;
            if( !pos ) {
                pos = root ,
                len = 0;
            }
            else {
                len = pos->len + 1 ,
                pos = pos->ch[t];
            }
        }
        pos->f[id] = max( pos->f[id] , len );
    }
}

inline void topo(int n) {
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
        int now = pos->len;
        for(int i=1;i<=n;i++)
            now = min( now , pos->f[i] );
        ans = max( ans , now );
        for(int i=1;i<=n;i++)
            pos->fa->f[i] = max( pos->fa->f[i] , pos->f[i] );
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

inline void getstr() {
    scanf("%d",&li);
    for(int i=0;i<li;i++)
        scanf("%d",in+i);
    for(int i=li-1;i;i--)
        in[i] = in[i] - in[i-1];
    --li;
    //for(int i=1;i<=li;i++) debug<<in[i]<<" ";debug<<endl;
}
int main() {
    freopen("dat.txt","r",stdin);
    static int n;
    scanf("%d",&n);n--;
    
    getstr();
    last = root = NewNode(0);
    for(int i=1;i<=li;i++)
        extend(in[i]);
    for(int i=1;i<=n;i++) {
        getstr();
        getans(i);
    }
    topo(n);
    
    printf("%d\n",ans+1);
    
    return 0;
}
