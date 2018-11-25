#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e6+1e2,maxl=23;

char in[maxn>>1];
int Log[maxn>>1],li,ans;

struct SuffixAutomatic {
    int ch[maxn][26],tc[maxn][26],fa[maxn],len[maxn],rit[maxn],root,last,cnt;
    int stk[maxn],sa[maxn>>1],rnk[maxn>>1],h[maxn>>1],rmq[maxn>>1][maxl],top,sal;
    SuffixAutomatic() { last = root = cnt = 1; }
    inline int NewNode(int ll) {
        return len[++cnt] = ll , cnt;
    }
    inline void extend(int x,int r) {
        int p = last , np = NewNode(len[p]+1); rit[np] = r;
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q] , fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void pre(int pos) {
        for(int i=0,t;i<26;i++) if( ( t = ch[pos][i] ) && len[t] == len[pos] + 1 ) {
            stk[++top] = i , tc[fa[t]][stk[len[t]-len[fa[t]]]] = t , pre(t) , stk[top--] = '\0';
        }
    }
    inline void dfs(int pos) {
        if( rit[pos] ) sa[++sal] = rit[pos];
        for(int i=0;i<26;i++) if( tc[pos][i] ) dfs(tc[pos][i]);
    }
    inline void geth(char* in,int li) {
        for(int i=1;i<=sal;i++) rnk[sa[i]] = i;
        reverse(in+1,in+1+li);
        for(int i=1,k=0;i<=sal;i++) {
            k -= (bool)k;
            const int p = sa[rnk[i]-1];
            while( in[i+k] == in[p+k] ) ++k;
            h[rnk[i]-1] = k;
        }
        reverse(in+1,in+1+li);
    }
    inline void initrmq() {
        for(int i=1;i<sal;i++) rmq[i][0] = h[i];
        for(int j=1;j<=Log[sal];j++) for(int i=1;i<sal;i++) rmq[i][j] = min( rmq[i][j-1] , rmq[i+(1<<(j-1))][j-1] );
    }
    inline int query(int l,int r) {
        l = rnk[l] , r = rnk[r];
        if( l > r ) swap(l,r);
        --r;
        int L = Log[r-l+1];
        return min( rmq[l][L] , rmq[r-(1<<L)+1][L] );
    }
    inline void work(char* in,int li) {
        for(int i=1;i<=li;i++) extend(in[i]-'a',li-i+1);
        pre(1) , dfs(1);
        in[li+1] = '#' , geth(in,li) , initrmq();
    }
}prf,suf;

inline int lcp(int i,int j) {
    return prf.query(i,j);
}
inline int lcs(int i,int j) {
    return suf.query(li-j+1,li-i+1);
}
inline void calc(int len) {
    for(int st=1,sst,lc;st+len<=li;st+=len) {
        sst = st + len , lc = lcp(st,sst) + lcs(st-1,sst-1);
        if( lc >= len ) {
            ans = max( ans , len * 2 );
        }
    }
}

int main() {
    scanf("%s",in+1) , li = strlen(in+1);
    for(int i=2;i<=li;i++) Log[i] = Log[i>>1] + 1;
    suf.work(in,li) , reverse(in+1,in+1+li) , prf.work(in,li) , reverse(in+1,in+1+li);
    for(int i=1;i<=li;i++) calc(i);
    printf("%d\n",ans);
    return 0;
}

