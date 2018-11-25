#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,lim=1e5;
const int mod=998244353;

char s[maxn];
int in[maxn];
int n,ans;

inline int& f(int i,int j,int k,int p) {
    static int arr[maxn][2][4][4];
    return arr[i][j][k+3][p+3];
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

inline void dp() { // 0 means l , 1 means z .
    f(0,0,0,0) = 1;
    for(int i=0;i<lim;i++) for(int j=0;j<2;j++) for(int k=0;k<=3;k++) for(int p=-3;p<=0;p++) if(f(i,j,k,p)) {
        if( k + 2 <= 3 ) adde(f(i+1,0,max(k+2,2),min(p+2,0)),f(i,j,k,p));
        if( p - 1 >= -3 ) adde(f(i+1,1,max(k-1,0),min(p-1,-1)),f(i,j,k,p));
    }
}

inline void getans() {
    int mx = 0 , mi = 0; ans = 1;
    for(int i=1,rit;i<=n;i++) { // diff at bit[i] .
        rit = n - i + 1;
        for(int j=0;j<in[i];j++) for(int k=0;k<=3;k++) for(int p=-3;p<=0;p++) if( mx + k <= 3 && mi + p >= -3 ) adde(ans,f(rit,j,k,p));
        if( !in[i] ) mx = max(mx+2,2) , mi = min(mi+2,0);
        else mx = max(mx-1,0) , mi = min(mi-1,-1);
    }
}


inline int findint(const string &x) {
    int ret = 0;
    for(unsigned i=0;i<x.length();i++) {
        if( isdigit(x[i]) ) ret = ret * 10 + x[i] - '0';
        else break;
    }
    return ret;
}
inline string cutint(const string &x) {
    int i;
    for(i=0;i<(signed)x.length();i++) if( !isdigit(x[i]) ) break;
    return x.substr(i,x.length()-i);
}
inline string explain(const string &x) {
    int i,j;
    for(i=0;i<(signed)x.length();i++) if( x[i] == '(' ) break;
    if( i == (signed)x.length() ) return x;
    int su = 0;
    for(j=0;j<(signed)x.length();j++) {
        if( x[j] == '(' ) ++su;
        else if( x[j] == ')' ) {
            if( su > 1 ) --su;
            else break;
        }
    }
    string ret = x.substr(0,i) , mid = x.substr(i+1,j-i-1) , rem = x.substr(j+1,x.length()-j-1) , rit = cutint(rem);
    int tim = findint(rem);
    mid = explain(mid);
    while(tim--) ret = ret + mid;
    ret = ret + explain(rit);
    return ret;
}
inline void explain() {
    string ss = s;
    string ex = explain(ss);
    n = ex.length();
    for(int i=1;i<=n;i++) in[i] = ex[i-1] == 'Z';
}

int main() {
    static int T;
    freopen("cadence.in","r",stdin);
    freopen("cadence.out","w",stdout);
    scanf("%d",&T) , dp();
    while(T-- ) {
        scanf("%s",s) , explain() , getans();
        printf("%d\n",ans);
    }
    fclose(stdout);
    return 0;
}
