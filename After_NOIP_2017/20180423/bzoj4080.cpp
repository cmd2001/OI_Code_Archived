#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
const int maxn=1e2+1e2;

int x[maxn],y[maxn],seq[maxn],n,d;
bool can[maxn][maxn],sel[maxn];
int way[maxn],ans;

inline bool judge(int id) {
    for(int i=1;i<id;i++) if( sel[i] && !can[seq[i]][seq[id]] ) return 0;
    return 1;
}
inline void calc() {
    int ret = 0;
    for(int i=1;i<=n;i++) if( judge(i) ) ret += sel[i] = 1;
    if( ret > ans ) {
        ans = 0;
        for(int i=1;i<=n;i++) if( sel[i] ) way[++ans] = seq[i];
    }
}
inline int dis(int a,int b) {
    const int dx = x[a] - x[b] , dy = y[a] - y[b];
    return dx * dx + dy * dy;
}

int main() {
    scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++) scanf("%d%d",x+i,y+i) , seq[i] = i;
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            can[i][j] = can[j][i] = ( dis(i,j) <= d * d );
    for(int i=1;i<=1000;i++) {
        std::random_shuffle(seq+1,seq+1+n) , memset(sel,0,sizeof(sel));
        calc();
    }
    printf("%d\n",ans) , std::sort(way+1,way+1+ans);
    for(int i=1;i<=ans;i++) printf("%d%c",way[i],i!=ans?' ':'\n');
    return 0;
}
