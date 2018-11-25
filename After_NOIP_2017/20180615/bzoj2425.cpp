#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=5e2+1e1,maxt=10;
const int prime[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47},pl=15;

char in[maxn];
int app[maxt],n;
lli ans;

struct Number {
    int dat[16];
    Number() { memset(dat,0,sizeof(dat)); }
    int& operator [] (const int &x) { return dat[x]; }
    const int& operator [] (const int &x) const { return dat[x]; }
    friend Number operator / (const Number &a,const Number &b) {
        Number ret;
        for(int i=1;i<=pl;i++) ret[i] = a[i] - b[i];
        return ret;
    }
    friend Number operator /= (Number &a,const Number &b) {
        return a = a / b;
    }
    inline lli build() {
        lli ret = 1;
        for(int i=1;i<=pl;i++) for(int j=1;j<=dat[i];j++) ret *= prime[i];
        return ret;
    }
};

inline Number fac(int x) {
    Number ret;
    for(int i=1,t=x;i<=pl;i++,t=x) while(t) ret[i] += t / prime[i] , t /= prime[i];
    return ret;
}
inline Number calc() {
    int su = 0;
    for(int i=0;i<10;i++) su += app[i];
    Number ret = fac(su);
    for(int i=0;i<10;i++) if( app[i] ) ret /= fac(app[i]);
    return ret;
}

inline void dp() {
    for(int i=1;i<=n;i++) {
        for(int j=0;j<in[i];j++) if( app[j] ) --app[j] , ans += calc().build() , ++app[j];
        --app[(int)in[i]];
    }
}

int main() {
    scanf("%s",in+1) , n = strlen(in+1);
    for(int i=1;i<=n;i++) ++app[(int)(in[i]=in[i]-'0')];
    dp() , printf("%lld\n",ans);
    return 0;
}
