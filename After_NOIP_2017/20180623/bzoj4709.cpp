#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],app[maxn],n;
lli su[maxn],f[maxn];
vector<int> stk[maxn];

template<typename T>
inline T top(const vector<T> &v) {
    return v[v.size()-1];
}
template<typename T>
inline T sec(const vector<T> &v) {
    return v[v.size()-2];
}

inline lli calc(int lft,lli su) {
    return f[lft-1] + in[lft] * su * su;
}
inline int bin(int i,int j) { // first sum make use i better than use j .
    int l = 0 , r = n + 1 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( calc(j,mid-su[j]+1) <= calc(i,mid-su[i]+1) ) r = mid;
        else l = mid;
    }
    return r;
}

int main() {
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++) {
        scanf("%d",in+i) , su[i] = ++app[x=in[i]];
        while( stk[x].size() >= 2 && bin(sec(stk[x]),top(stk[x])) <= bin(top(stk[x]),i) ) stk[x].pop_back();
        stk[x].push_back(i);
        while( stk[x].size() >= 2 && bin(sec(stk[x]),top(stk[x])) <= su[i] ) stk[x].pop_back();
        f[i] = calc(top(stk[x]),su[i]-su[top(stk[x])]+1);
    }
    printf("%lld\n",f[n]);
    return 0;
}

