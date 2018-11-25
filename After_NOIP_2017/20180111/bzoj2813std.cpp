#define Troy 
 
#include <algorithm>
#include <cstdio>
 
using namespace std;
 
inline int read(){
    int s=0,k=1;char ch=getchar();
    while(ch<'0'|ch>'9')  ch=='-'?k=-1:0,ch=getchar();
    while(ch>47&ch<='9')  s=s*10+(ch^48),ch=getchar();
    return s*k;
}
 
typedef long long ll;
 
const int N=6e3;
 
ll Hash[N];int cnt=0;
ll f[22][22][N];
 
inline int find(ll x){
    return upper_bound(Hash+1,Hash+cnt+1,x)-Hash-1;
}
 
inline void init(){
    for(ll x=1;x<=1e9;x*=2)
        for(ll y=x;y<=1e9;y*=3)
            for(ll z=y;z<=1e9;z*=5)
                for(ll w=z;w<=1e9;w*=7)
                    Hash[++cnt]=w;  //cnt=5194
    sort(Hash+1,Hash+cnt+1);
    for(int i=1;i<=9;i++)
        f[1][i][i]=1;
    for(int i=2;i<=18;i++)            
        for(int k=1;k<=cnt;k++)
            for(int j=1;j<=9;j++)
                if(Hash[k]%j==0){
                    int x=find(Hash[k]/j);
                    for(int l=1;l<=9;l++)
                        f[i][j][k]+=f[i-1][l][x];
                }
}
 
int p[20],m;
 
inline ll solve(ll x,int pos){
    if(x==0)    return 0;
    ll t=1;
    int tt=pos;
    m=0;while(x)  p[++m]=x%10,x/=10,t*=p[m];
    ll ret=0;
    if(t==Hash[pos])  ret++;
    for(int i=1;i<m;i++)
        for(int j=1;j<=9;j++)
            ret+=f[i][j][pos];
    for(int i=m;i;i--){
        for(int j=1;j<p[i];j++)
            ret+=f[i][j][pos];
        if(p[i]==0) break;
        if(Hash[pos]%p[i]!=0)
            break;
        pos=find(Hash[pos]/p[i]);
    }
    return ret;
}
 
inline ll calc(ll x){
    ll ret=0;
    for(int i=1;i<=cnt;i++){
        ret+=solve(x/Hash[i],i);
    }
    return ret;
}
 
int main(){
    //freopen("umnozak.in","r",stdin);
    //freopen("umnozak.out","w",stdout);
    init();
    ll L,R;
    scanf("%lld%lld",&L,&R);
    printf("%lld\n",calc(R)-calc(L-1));
}