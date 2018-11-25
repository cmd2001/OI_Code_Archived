#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

char s[maxn];
int in[maxn],sa[maxn],rnk[maxn],tp[maxn],tex[maxn];
int n,m,t;

inline void Resort() {
    memset(tex,0,sizeof(int)*m);
    for(int i=1;i<=n;i++) ++tex[rnk[tp[i]]];
    for(int i=1;i<=m;i++) tex[i] += tex[i-1];
    for(int i=n;i;i--) sa[tex[rnk[tp[i]]]--] = tp[i];
}
inline bool cmp(int* f,int a,int b,int l) {
    return f[a] == f[b] && f[a+l] == f[b+l];
}
inline void Build() {
    m = 127;
    for(int i=1;i<=n;i++) rnk[i] = in[i] , tp[i] = i;
    Resort();
    for(int w=1,p=1;w<n;w<<=1,m=p) {
        p = 0;
        for(int i=n-w+1;i<=n;i++) tp[++p] = i;
        for(int i=1;i<=n;i++) if( sa[i] > w ) tp[++p] = sa[i] - w;
        Resort(); swap(rnk,tp); rnk[sa[1]] = p = 1;
        for(int i=2;i<=n;i++)
            rnk[sa[i]] = cmp(tp,sa[i],sa[i-1],w) ? p : ++p;
    }
}

int main() {
    scanf("%s",s);
    n = strlen(s);
    for(int i=0;i<n;i++)
        in[i+1] = s[i] , in[i+1+n] = s[i];
    n <<= 1;
    Build();
    t = n >> 1;
    for(int i=1;i<=n;i++)
        if( sa[i] <= t )
            putchar(in[sa[i]+t-1]);
    putchar('\n');
    return 0;
}
