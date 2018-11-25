#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=5e2+1e1;
const long double eps=1e-8;

int m;

struct Equation {
    long double dat[maxn];
    Equation() { memset(dat,0,sizeof(dat)); }
    const long double& operator [] (const int &x) const { return dat[x]; }
    friend Equation operator * (const Equation &a,const long double &b) {
        Equation ret;
        for(int i=1;i<=m;i++) ret.dat[i] = a[i] * b;
        return ret;
    }
    friend Equation operator - (const Equation &a,const Equation &b) {
        Equation ret;
        for(int i=1;i<=m;i++) ret.dat[i] = a[i] - b[i];
        return ret;
    }
};

struct LinearBase {
    Equation dat[maxn];
    bool vis[maxn];
    inline bool insert(Equation t) {
        for(int i=1;i<=m;i++)
            if( abs(t[i]) > eps ) {
                if( !vis[i] ) return dat[i] = t , vis[i] = 1;
                else t = t - dat[i] * ( t[i] / dat[i][i] );
            }
        return 0;
    }
}lb;

struct Node {
    Equation e;
    int val;
    friend bool operator < (const Node &a,const Node &b) {
        return a.val < b.val;
    }
}ns[maxn];

int main() {
    static int n,su;
    static long long ans;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%Lf",ns[i].e.dat+j);
    for(int i=1;i<=n;i++) scanf("%d",&ns[i].val);
    sort(ns+1,ns+1+n);
    for(int i=1;i<=n;i++) if( lb.insert(ns[i].e) ) ++su , ans += ns[i].val;
    printf("%d %lld\n",su,ans);
    return 0;
}
