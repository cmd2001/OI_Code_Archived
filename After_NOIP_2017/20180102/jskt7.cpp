#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

char in[maxn>>1],out[maxn];
int nn,li,ol,cnt,ans;
unsigned cc;

struct Node {
    Node *fa,*ch[26];
    int len,deg;
    bitset<105> bs;
}ns[maxn],*last,*root;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
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
                p = p->fa;
        }
    }
    last = np;
}

inline void EX_extend(int x,int id) {
    if( last->ch[x] ) {
        Node *p = last , *q = last->ch[x];
        if( q->len == p->len + 1 )
            last = q;
        else {
            Node* npq = NewNode(p->len+1);
            memcpy(npq->ch,q->ch,sizeof(q->ch));
            npq->fa = q->fa;
            q->fa = npq;
            while( p && p->ch[x] == q )
                p->ch[x] = npq,
                p = p->fa;
            last = npq;
        }
    }
    else
        extend(x);
    last->bs[id] = 1;
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
        if( pos->bs.count() > cc )
            ans = max( ans , pos->len );
        pos->fa->bs |= pos->bs;
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

inline void dfs(Node* pos) {
    if( pos->len > ans )
        return;
    if( pos->len == ans && pos->bs.count() > cc ) {
        puts(out);
        return;
    }
    for(int i=0;i<26;i++)
        if( pos->ch[i] && pos->ch[i]->len == pos->len + 1 ) {
            out[ol++] = 'a' + i;
            dfs(pos->ch[i]);
            out[--ol] = '\0';
        }
}

int main() {
    //freopen("wa.txt","w",stdout);
    scanf("%d",&nn);
    cc = nn >> 1;
    
    root = NewNode(0);
    for(int i=1;i<=nn;i++) {
        scanf("%s",in+1);
        li = strlen(in+1);
        last = root;
        for(int j=1;j<=li;j++)
            EX_extend(in[j]-'a',i);
    }
    
    topo();
    if( ans )
        dfs(root);
    else
        puts("?");
    
    return 0;
}