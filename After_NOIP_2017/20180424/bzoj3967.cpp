#include<cstdio>
#include<tr1/unordered_map>
typedef unsigned long long int ulli;
const ulli inf = 1ull<<63;
const ulli prime[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

ulli c[65][65];
std::tr1::unordered_map<ulli,ulli> mp;

inline void initc() {
    c[0][0] = 1;
    for(int i=1;i<=63;i++) {
        c[i][0] = 1;
        for(int j=1;j<=i;j++) {
            if( c[i-1][j-1] < inf && c[i-1][j] < inf ) c[i][j] = c[i-1][j-1] + c[i-1][j];
            else c[i][j] = inf;
            if( c[i][j] > inf ) c[i][j] = inf;
        }
    }
}
inline void dfs(int pos,int su,ulli mul,ulli way) {
    if( pos > 15 ) return;
    if( su && ( mp.find(way) == mp.end() || mul < mp[way] ) ) mp[way] = mul;
    int cur = 0;
    while( prime[pos] <= inf / mul && c[su+cur+1][cur+1] <= inf / way ) {
        mul *= prime[pos] , ++cur;
        dfs(pos+1,su+cur,mul,way*c[su+cur][cur]);
    } 
}

int main() {
    static ulli k;
    initc() , dfs(0,0,1,1);
    while( scanf("%llu",&k) == 1 ) printf("%llu %llu \n",k,mp[k]);
    return 0;
}
