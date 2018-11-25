#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=3e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

char in[maxn];
int a[maxn],n,m,cnt;
lli siz[maxn],ans[maxn];

struct Node {
    Node *fa,*ch[26];
    lli mx[2],mi[2],siz;
    int len,deg;
    Node() {
        mx[0] = mx[1] = -inf,
        mi[0] = mi[1] = inf;
    }
}ns[maxn<<1],*last,*root;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}

inline void extend(int x,int pos) {
    Node* p = last;
    Node* np = NewNode(last->len+1);
    np->mx[0] = np->mi[0] = a[pos];
    np->siz = 1;
    
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

inline void updatemin(lli* dst,lli sou) {
    if( sou <= *dst )
        dst[1] = *dst , *dst = sou;
    else if( sou < dst[1] )
        dst[1] = sou;
}
inline void updatemax(lli* dst,lli sou) {
    if( sou >= *dst )
        dst[1] = *dst , *dst = sou;
    else if( sou > dst[1] )
        dst[1] = sou;
}
inline void Process(const Node* now) {
    siz[now->len] += now->siz * ( now->siz - 1 ) >> 1;
    if( now->siz >= 2 )
        ans[now->len] = max( ans[now->len] , max( now->mx[0] * now->mx[1] , now->mi[0] * now->mi[1] ) );
    if( now == root ) {
        //debug<<"root->siz = "<<now->siz<<endl;
        return;
    }
    siz[now->fa->len] -= now->siz * ( now->siz - 1 ) >> 1;
    now->fa->siz += now->siz;
    updatemin(now->fa->mi,now->mi[0]) , updatemin(now->fa->mi,now->mi[1]);
    updatemax(now->fa->mx,now->mx[0]) , updatemax(now->fa->mx,now->mx[1]);
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
        Process(pos);
        if( pos == root )
            break;
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

int main() {
    scanf("%d",&n);
    scanf("%s",in+1);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    
    reverse(in+1,in+1+n);
    reverse(a+1,a+1+n);
    last = root = NewNode(0);
    for(int i=1;i<=n;i++)
        extend(in[i]-'a',i);
    for(int i=0;i<=n;i++)
        ans[i] = -inf;
    
    topo();
    
    for(int i=n-1;~i;i--)
        if( siz[i+1] )
            siz[i] += siz[i+1],
            ans[i] = max( ans[i] , ans[i+1] );
    for(int i=0;i<=n;i++)
        if( ans[i] == -inf )
            ans[i] = 0;
    
    for(int i=0;i<n;i++)
        printf("%lld %lld\n",siz[i],ans[i]);
    
    return 0;
}