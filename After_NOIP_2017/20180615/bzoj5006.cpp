#include<cstdio>
#include<tr1/unordered_map>
typedef long long int lli;
const int maxn=16,maxe=maxn*maxn<<1;
const int mod=1e9+7,inv2=(mod+1)>>1,inv4=inv2>>1;

int s[maxe],o[maxe],bin[maxn<<1];
int cnt;

std::tr1::unordered_map<int,int> mp;

inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &x,const int &y) {
    if( ( x += y ) >= mod ) x -= mod;
}
inline int dfs(int S) {
    if( !S ) return 1;
    if( mp.find(S) != mp.end() ) return mp[S];
    int ret = 0;
    for(int i=1;i<=cnt;i++) if( ( ( S & s[i] ) == s[i] ) && S < ( s[i] << 1 ) ) adde(ret,mul(dfs(S^s[i]),o[i]));
    return mp[S] = ret;
}

int main() {
    int n,m,ans;
    scanf("%d%d",&n,&m);
    bin[1] = 1; for(int i=2;i<=n<<1;i++) bin[i] = bin[i-1] << 1;
    for(int i=1,tpe,x,y,a,b;i<=m;i++) {
        scanf("%d%d%d",&tpe,&x,&y) , s[++cnt] = bin[x] | bin[y+n] , o[cnt] = inv2;
        if( tpe) {
            scanf("%d%d",&a,&b) , s[++cnt] = bin[a] | bin[b+n] , o[cnt] = inv2;
            if( ( bin[x] | bin[y+n] ) & ( bin[a] | bin[b+n] ) ) continue;
            s[++cnt] = bin[x] | bin[y+n] | bin[a] | bin[b+n] , o[cnt] = tpe == 1 ? inv4 : mod - inv4;
        }
    }
    ans = mul(dfs((1<<(n<<1))-1),1<<n) , printf("%d\n",ans);
    return 0;
}