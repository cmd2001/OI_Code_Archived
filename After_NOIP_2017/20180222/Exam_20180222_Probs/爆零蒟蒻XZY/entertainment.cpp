#include<cstdio>
#include<algorithm>
const int maxn=1e2+1e1;

int in[maxn][2],sta[maxn];
int n,k,ms,me,ans;

inline void judge() {
    int ss = 0 , se = 0 , sum = 0;
    for(int i=1;i<k;i++) ss += sta[i] == 1 , se += sta[i] == 2 , sum += in[i][sta[i]-1];
    for(int i=k;i<=n;i++) {
        ss += sta[i] == 1 , se += sta[i] == 2 , sum += in[i][sta[i]-1];
        ss -= sta[i-k] == 1 , se -= sta[i-k] == 2;
        if( ss < ms || se < me ) return;
    }
    ans = std::max(ans,sum);
}
inline void dfs(int pos) {
    if( pos > n ) return judge();
    sta[pos] = 1 , dfs(pos+1) ,
    sta[pos] = 2 , dfs(pos+1) ;
}

int main() {
    freopen("entertainment.in","r",stdin);
    freopen("entertainment.out","w",stdout);
    scanf("%d%d%d%d",&n,&k,&ms,&me) , ans = -0x7fffffff;
    for(int i=1;i<=n;i++) scanf("%d",in[i]);
    for(int i=1;i<=n;i++) scanf("%d",in[i]+1);
    dfs(1);
    printf("%d\n",ans);
    fclose(stdout);
    return 0;
}
