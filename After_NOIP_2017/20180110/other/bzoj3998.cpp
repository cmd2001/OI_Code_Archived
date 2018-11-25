#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

char in[maxn>>1];
int que[maxn],bu[maxn];
int ch[maxn][26],fa[maxn],len[maxn];
lli sum[maxn],sizr[maxn];
int root,last,li,cnt,T,k;

inline int NewNode(int ll) {
    len[++cnt] = ll;
    return cnt;
}
inline void extend(int x) {
    int p = last;
    int np = NewNode(len[p]+1);
    sizr[np] = 1;
    while( p && !ch[p][x] )
        ch[p][x] = np,
        p = fa[p];
    if( !p )
        fa[np] = root;
    else {
        int q = ch[p][x];
        if( len[q] == len[p] + 1 )
            fa[np] = q;
        else {
            int nq = NewNode(len[p]+1);
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while( p && ch[p][x] == q )
                ch[p][x] = nq,
                p = fa[p];
        }
    }
    last = np;
}
inline void pre() {
    for(int i=1;i<=cnt;i++)
        ++bu[len[i]];
    for(int i=1;i<=li;i++)
        bu[i] += bu[i-1];
    for(int i=1;i<=cnt;i++)
        que[bu[len[i]]--] = i;
    for(int i=cnt;i;i--) {
        const int now = que[i];
        if( T == 1 ) { // calc by sizr.
            if( fa[now] && fa[now] != root )
                sizr[fa[now]] += sizr[now];
        }
        else {
            if( now != root )
                sizr[now] = 1;
        }
    }
    for(int i=cnt;i;i--) {
        const int now = que[i];
        sum[now] = sizr[now];
        for(int j=0;j<26;j++)
            if( ch[now][j] )
                sum[now] += sum[ch[now][j]];
    }
}
inline void kth(int k) {
    if( k > sum[root] ) {
        puts("-1");
        return;
    }
    int now = root;
    while( k ) {
        for(int i=0;i<26;i++)
            if( ch[now][i] ) {
                if( k <= sum[ch[now][i]] ) {
                    putchar('a'+i);
                    now = ch[now][i];
                    k = max( k - sizr[now] , 0LL );
                    break;
                }
                else
                    k -= sum[ch[now][i]];
            }
    }
    putchar('\n');
}

int main() {
    scanf("%s%d%d",in+1,&T,&k);
    li = strlen(in+1);
    
    last = root = NewNode(0);
    for(int i=1;i<=li;i++)
        extend(in[i]-'a');
    
    pre();
    /*for(int i=1;i<=cnt;i++)
        debug<<sum[i]<<" ";debug<<endl;*/
    kth(k);
    
    return 0;
}