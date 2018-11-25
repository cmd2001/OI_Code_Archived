#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;
const int inf=0x3f3f3f3f;

char in[maxn>>1];
int m,li,cnt,l,r;

struct Node {
    Node *fa,*ch[26];
    int len,mir,deg;
    lli siz;
    Node() {
        mir = inf;
    }
}ns[maxn],*last,*root;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}

inline void extend(int x,int pos) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
    np->mir = pos ;
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

inline int dfs(Node* pos) {
    if( pos->siz )
        return pos->siz;
    lli ret = 0;
    for(int i=0;i<26;i++)
        if( pos->ch[i] )
            ret += dfs(pos->ch[i]);
    return pos->siz = ret + ( pos != root );
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
        pos->fa->mir = min( pos->fa->mir , pos->mir );
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

inline void query(lli k) {
    if( k > root->siz ) {
        l = r = 0;
        return;
    }
    Node* now = root;
    int len = 0;
    while( k ) {
        for(int i=0;i<26;i++)
            if( now->ch[i] ) {
                if( k <= now->ch[i]->siz ) {
                    ++len;
                    --k;
                    now = now->ch[i];
                    break;
                }
                else
                    k -= now->ch[i]->siz;
            }
    }
    r = now->mir;
    l = r - len + 1;
}

int main() {
    scanf("%s",in+1);
    li = strlen(in+1);
    
    last = root = NewNode(0);
    for(int i=1;i<=li;i++)
        extend(in[i]-'a',i);
    dfs(root);
    topo();
    
    lli k;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) {
        scanf("%lld",&k);
        k = ( k ^ ((lli)l) ^ ((lli)r) ) + 1;
        query(k);
        printf("%d %d\n",l,r);
    }
    return 0;
}