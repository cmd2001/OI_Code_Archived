#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
using namespace std;
const int maxn=53,maxe=127;
const int mod=45989;

vector<pair<int,int> > es[maxn]; // edge<target,id> .
int id[maxn][maxe],iid;
int n,m,len,st,ed,step,sum;

struct Matrix {
    int dat[maxe][maxe];
    Matrix(int tpe=0) { memset(dat,0,sizeof(dat)); for(int i=1;i<=len;i++) dat[i][i] = tpe; }
    int* operator [] (const int &x) { return dat[x]; }
    const int* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=len;i++)
            for(int j=1;j<=len;j++)
                for(int k=1;k<=len;k++)
                    ret[i][j] = ( ret[i][j] + a[i][k] * b[k][j] % mod ) % mod;
        return ret;
    }
}ans,trans;

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}

inline void getid(int pos) {
    for(unsigned i=0;i<es[pos].size();i++) id[pos][es[pos][i].first] = ++iid;
}
inline void buildtrs(int pos,int from) {
    for(unsigned i=0;i<es[pos].size();i++) if( es[pos][i].first != from ) trans[id[pos][from]][id[es[pos][i].second][es[pos][i].first]] = 1;
}

int main() {
    scanf("%d%d%d%d%d",&n,&m,&step,&st,&ed) , ++st , ++ed;
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , ++a , ++b , es[a].push_back(make_pair(i,b)) , es[b].push_back(make_pair(i,a));
    es[st].push_back(make_pair(0,0));
    for(int i=1;i<=n;i++) getid(i);
    for(int i=1;i<=n;i++) for(unsigned j=0;j<es[i].size();j++) buildtrs(i,es[i][j].first);
    ans[1][id[st][0]] = 1 , len = iid;
    ans = ans * fastpow(trans,step);
    for(int i=1;i<=m;i++) if( id[ed][i] ) sum = ( sum + ans[1][id[ed][i]] ) % mod;
    printf("%d\n",sum);
    return 0;
}
