#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2.5e5+1e2;

char a[maxn],b[maxn];
int la,lb,cnt,ans;

struct Node {
    Node *fa,*nxt[26];
    int len;
}ns[maxn],*root,*last;

Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}

inline void extend(int x) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
    while( p && !p->nxt[x] )
        p->nxt[x] = np,
        p = p->fa;
    if( !p )
        np->fa = root;
    else {
        Node* q = p->nxt[x];
        if( q->len == p->len + 1 )
            np->fa = q;
        else {
            Node* nq = NewNode(p->len+1);
            memcpy(nq->nxt,q->nxt,sizeof(q->nxt));
            nq->fa = q->fa;
            q->fa = np->fa = nq;
            while( p && p->nxt[x] == q )
                p->nxt[x] = nq,
                p = p->fa; // ?
        }
    }
    last = np;
}

inline void getans() {
    static int len = 0;
    Node* now = root;
    for(int i=1;i<=lb;i++) {
        if( now->nxt[(int)b[i]] )
            ++len,
            now = now->nxt[(int)b[i]];
        else {
            while( now && !now->nxt[(int)b[i]] )
                now = now -> fa;
            if( !now )
                now = root,
                len = 0;
            else
                len = now->len + 1,
                now = now->nxt[(int)b[i]];
        }
        ans = max( ans , len );
    }
}

int main() {
    scanf("%s%s",a+1,b+1);
    la = strlen(a+1),
    lb = strlen(b+1);
    
    for(int i=1;i<=la;i++)
        a[i] -= 'a';
    for(int j=1;j<=lb;j++)
        b[j] -= 'a';
    
    last = root = NewNode(0);
    for(int i=1;i<=la;i++)
        extend(a[i]);
    getans();
    
    printf("%d\n",ans);
    
    return 0;
}