#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5e5+1e2;

char a[maxn>>1],b[maxn>>1];
int la,lb,cnt,ans;

struct Node {
    Node* fa,*ch[26];
    int len;
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
        ans = max( ans , len );
    }
}

int main() {
    scanf("%s%s",a+1,b+1);
    la = strlen(a+1) ,
    lb = strlen(b+1) ;
    
    last = root = NewNode(0);
    for(int i=1;i<=la;i++)
        extend(a[i]-'a');
    
    getans();
    
    printf("%d\n",ans);
    
    return 0;
}