#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ulli unsigned long long int
#define lli long long int
using namespace std;
const int maxn=2e2+1e1+1,maxm=1e5+1e2+1;
const ulli base = 233;
const int inf=0x3f3f3f3f;

char in[maxm];
int len[maxn];
vector<ulli> hsh[maxn];
ulli pows[maxm];
int n,m;

struct Matrix {
    lli dat[maxn][maxn];
    Matrix() {
        memset(dat,0x3f,sizeof(dat));
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    ret.dat[i][j] = min( ret.dat[i][j] , a.dat[i][k] + b.dat[k][j] );
        return ret;
    }
}ans,dis;

inline ulli segment(const vector<ulli> &v,int st,int ed) {
    --st;
    return v[ed] - v[st] * pows[ed-st];
}
inline void init(int id) {
    len[id] = strlen(in+1);
    hsh[id].resize(len[id]+10);
    for(int i=1;i<=len[id];i++)
        hsh[id][i] = hsh[id][i-1] * base + ( in[i] - 'a' + 1 );
}
inline void initpows() {
    pows[0] = 1;
    for(int i=1;i<maxm;i++)
        pows[i] = pows[i-1] * base;
}

inline int calcdis(int i,int j) {
    for(int sme = min( len[i] , len[j] ) - 1; sme ; sme-- ) {
        if( segment(hsh[i],len[i]-sme+1,len[i]) == segment(hsh[j],1,sme) )
            return len[j] - sme;
    }
    return len[j];
}
inline void initdis() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dis.dat[i][j] = calcdis(i,j);
}

inline Matrix fastpow(Matrix base,int tme) {
    Matrix ret;
    for(int i=1;i<=n;i++) ret.dat[i][i] = 0;
    while( tme ) {
        if( tme & 1 ) ret = ret * base;
        base = base * base;
        tme >>= 1;
    }
    return ret;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%s",in+1);
        init(i);
    }
    initpows();
    initdis();
    
    ans = fastpow(dis,m-1);
    
    lli t = 0x3f3f3f3f3f3f3f3fll;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            t = min( t , len[i] + ans.dat[i][j] );
        }
    }
    
    printf("%lld\n",t);
    
    return 0;
}



