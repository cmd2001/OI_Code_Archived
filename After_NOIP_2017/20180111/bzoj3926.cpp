#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],s[maxn],t[maxn<<1],nxt[maxn<<1],deg[maxn<<1];
int li,cnt;
lli ans;

struct Node {
    Node *fa,*ch[10];
    int len,deg;
}ns[maxn*30],*root;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns + cnt;
}
inline Node* extend(int x,Node* last) {
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
    return np;
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    ++deg[to] ,
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to) {
    addedge(from,to) , addedge(to,from);
}

inline void dfs(int pos,int fa,Node* last) {
    Node* now = extend(in[pos],last);
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa )
            dfs(t[at],pos,now);
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
        ans += pos->len - pos->fa->len;
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

int main() {
    static int n;
    scanf("%d%*d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        doubledge(a,b);
    }
    
    root = NewNode(0);
    for(int i=1;i<=n;i++)
        if( deg[i] == 1 )
            dfs(i,-1,root);
    topo();
    
    printf("%lld\n",ans);
    
    return 0;
}