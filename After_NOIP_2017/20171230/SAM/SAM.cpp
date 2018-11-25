#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2;

struct Node {
    int mx;
    Node *par,*nxt[26];
}ns[maxn],*root,*last;

inline Node* NewNode(int len) {
    static int cnt = 0;
    ns[++cnt].mx = len;
    return &ns[cnt];
}

inline void extend(int x) {
    Node *p = last;
    Node *np = NewNode(p->mx+1);
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

