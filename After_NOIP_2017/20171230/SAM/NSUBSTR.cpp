#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

char in[maxn];
int f[maxn],len,cnt;

struct Node {
    int mx;
    Node *par,*nxt[26];
    int right,deg;
}ns[maxn],*root,*last;

inline Node* NewNode(int len) {
    ns[++cnt].mx = len;
    return &ns[cnt];
}

inline void extend(int x) {
    Node *p = last;
    Node *np = NewNode(p->mx+1);
    np->right = 1;
    while( p && !p->nxt[x] )
        p->nxt[x] = np,
        p = p->par;
    if( !p )
        np->par = root;
    else {
        Node* q = p->nxt[x];
        if( q->mx == p->mx + 1 )
            np->par = q;
        else {
            Node* nq =NewNode(p->mx+1);
            memcpy(nq->nxt,q->nxt,sizeof(q->nxt));
            nq->par = q->par;
            q->par = np->par = nq;
            while( p && p->nxt[x] == q )
                p->nxt[x] = nq,
                p = p->par;
        }
    }
    last = np;
}

inline void topo() {
    queue<int> q;
    for(int i=1;i<=cnt;i++)
        if( &ns[i] != root )
            ++ns[i].par->deg;
    for(int i=1;i<=cnt;i++)
        if( !ns[i].deg )
            q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        if( &ns[pos] == root )
            break;
        ns[pos].par->right += ns[pos].right;
        f[ns[pos].mx] = max( f[ns[pos].mx] , ns[pos].right );
        --ns[pos].par->deg;
        if( !ns[pos].par->deg )
            q.push( ns[pos].par - ns );
    }
}

inline void calc() {
    for(int i=len-1;i;i--)
        f[i] = max( f[i] , f[i+1] );
}

int main() {
    scanf("%s",in+1);
    len = strlen(in+1);
    
    last = root = NewNode(0);
    for(int i=1;i<=len;i++)
        extend(in[i]-'a');
    
    topo();
    calc();
    
    for(int i=1;i<=len;i++)
        printf("%d\n",f[i]);
    
    return 0;
}
