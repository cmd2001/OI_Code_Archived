#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=3e5+1e2;
const int inf=0x3f3f3f3f;

char a[maxn>>1],b[maxn>>1];
int la,lb,cnt,ans,T;

struct Node {
    Node* fa,*ch[26];
    int len,deg,f[12];
}ns[maxn],*root,*last;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns + cnt;
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
                p = p-> fa;
        }
    }
    last = np;
}

inline void getans() {
    int len = 0;
    Node* now = root;
    for(int i=1;i<=lb;i++) {
        const int t = b[i] - 'a';
        if( now->ch[t] ) {
            now = now->ch[t],
            ++len;
        }
        else {
            while( now && !now->ch[t] )
                now = now->fa;
            if( !now )
                now = root,
                len = 0;
            else
                len = now->len + 1,
                now = now->ch[t];
        }
        now->f[T] = max( now->f[T] , len );
    }
}
inline void cunt() {
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
        for(int i=1;i<=T;i++)
            pos->fa->f[i] = max( pos->fa->f[i] , pos->f[i] );
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
    for(int i=1,nw;i<=cnt;i++) {
        if( ns + i == root )
            continue;
        nw = inf;
        for(int j=1;j<=T;j++)
            nw = min( nw , ns[i].f[j] );
        nw = min( nw , ns[i].len ); // ?
        ans = max( ans , nw );
    }
}

int main() {
    scanf("%s",a+1);
    la = strlen(a+1) ,
    
    last = root = NewNode(0);
    for(int i=1;i<=la;i++)
        extend(a[i]-'a');
    
    while( scanf("%s",b+1) == 1 ) {
        ++T;
        lb = strlen(b+1);
        getans();
    }
    
    cunt();
    
    printf("%d\n",ans);
    
    return 0;
}