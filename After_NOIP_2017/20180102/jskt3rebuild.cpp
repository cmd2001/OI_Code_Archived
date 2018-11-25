#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

char in[maxn];
int fa[maxn],ch[maxn][26],tc[maxn][26],len[maxn],rig[maxn],root,last,cnt;
int stk[maxn],top;
int sa[maxn],rnk[maxn],height[maxn],sal;
lli sum[maxn],l,r,v;
int m,li;

inline int NewNode(int ll) {
    len[++cnt] = ll;
    return cnt;
}
inline void extend(int x,int pos) {
    int p = last;
    int np = NewNode(len[p]+1);
    rig[np] = pos;
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

inline void pre(int pos) {
    for(int i=0;i<26;i++)
        if( ch[pos][i] && len[ch[pos][i]] == len[pos] + 1 ) {
            const int &x = ch[pos][i];
            stk[++top] = i;
            tc[fa[x]][stk[len[x]-len[fa[x]]]] = x;
            pre(x);
            stk[top--] = '\0';
        }
}
inline void dfs(int pos) {
    if( rig[pos] )
        sa[++sal] = rig[pos];
    for(int i=0;i<26;i++)
        if( tc[pos][i] )
            dfs(tc[pos][i]);
}

inline void calh() {
    for(int i=1;i<=li;i++)
        rnk[sa[i]] = i;
    int k = 0;
    for(int i=1;i<=li;i++) {
        const int p1 = i , p2 = sa[rnk[i]-1];
        if(k)
            k--;
        while( p1+k<=li && p2+k<=li && in[p1+k] == in[p2+k] )
            ++k;
        height[rnk[i]-1] = k;
    }
}

int main() {
    scanf("%s",in+1);
    li = strlen(in+1);
    
    last = root = NewNode(0);
    for(int i=li;i;i--)
        extend(in[i]-'a',i);
    pre(root),
    dfs(root);
    
    calh();
    
    for(int i=1;i<=li;i++)
        sum[i] = sum[i-1] + li - ( sa[i] - 1 ) - height[i-1];
    
    /*for(int i=1;i<=li;i++) debug<<sa[i]<<" ";debug<<endl;
    for(int i=0;i<li;i++) debug<<height[i]<<" ";debug<<endl;
    for(int i=1;i<=li;i++) debug<<sum[i]<<" ";debug<<endl;*/
    
    scanf("%d",&m);
    
    while(m--) {
        scanf("%lld",&v);
        v = ( v ^ l ^ r ) + 1;
        if( v > sum[li] )
            l = r = 0;
        else {
            int pos = lower_bound(sum+1,sum+1+li,v) - sum;
            //debug<<"pos = "<<pos<<endl;
            l = sa[pos] ;
            int len = height[pos-1] + v - sum[pos-1];
            //debug<<"len = "<<len<<endl;
            for(int i=pos+1;i<=li&&height[i-1]>=len;i++)
                l = min( l , (lli)sa[i] );
            r = l + len - 1;
            //debug<<l<<" "<<r<<endl;
        }
        printf("%lld %lld\n",l,r);
    }
    return 0;
}
