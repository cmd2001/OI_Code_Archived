#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=3e6+1e2;

char in[maxn];
int mth[maxn];
int cnt,li;
int f[maxn>>1],q[maxn>>1],st,ed;

struct Node {
    Node *fa,*ch[2];
    int len;
}ns[maxn],*root,*last;

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
inline void insert(char* s,int len) {
    last = root;
    for(int i=1;i<=len;i++)
        extend(s[i]-'0');
}

inline void match() {
    Node* now = root;
    int len = 0;
    for(int i=1;i<=li;i++) {
        const int t = in[i] - '0';
        if( now->ch[t] )
            len++ , now = now->ch[t];
        else {
            while( now && !now->ch[t] ) {
                now = now->fa;
            }
            if( !now )
                now = root , len = 0;
            else
                len = now->len + 1 , now = now->ch[t];
        }
        mth[i] = len;
    }
}

inline void reset() {
    for(int i=0;i<=li+1;i++)
        f[i] = 0;
    for(int i=0;i<=ed+1;i++)
        q[i] = 0;
    st = 1 , ed = 0;
}
inline bool judge(int lim) {
    reset();
    q[++ed] = 0;
    for(int i=1;i<=li;i++) {
        f[i] = f[i-1];
        const int fst = i - lim;
        if( fst > 0 ) {
            while( ed >= st && f[fst] - fst >= f[q[ed]] - q[ed] )
                --ed;
            q[++ed] = fst;
        }
        while( ed >= st && q[st] < i - mth[i] )
            ++st;
        if( ed >= st && i - q[st] >= lim )
            f[i] = max( f[i] , f[q[st]] + i - q[st] );
    }
    return 10 * f[li] >= 9 * li;
}

inline int getans() {
    int ll = 0 , rr = li+1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) )
            ll = mid;
        else
            rr = mid;
    }
    return ll;
}

inline void getstr(char* dst,int& len) {
    char ch; len=0;
    while( !isdigit(ch=getchar()) );
    do dst[++len]=ch; while( isdigit(ch=getchar()) );
}
inline int getint() {
    int ret=0,ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int n,m;
    n = getint() , m = getint();
    
    last = root = NewNode(0);
    for(int i=1;i<=m;i++) {
        getstr(in,li);
        insert(in,li);
    }
    for(int i=1;i<=n;i++) {
        getstr(in,li);
        match();
        printf("%d\n",getans());
    }
    
    return 0;
}