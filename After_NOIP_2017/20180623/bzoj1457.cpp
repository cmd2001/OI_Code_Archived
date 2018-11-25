#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=1e2+1e1;

bool vis[maxn*3];
int sg[maxn][maxn]; // sg == 0 means first player wins .

inline bool one_Step(int x,int y) {
    return x == y || !x || !y;
}
inline int calc_Mex() {
    for(int i=0;i<300;i++) if( !vis[i] ) return i;
    return 300;
}
inline void mark_Point(int x,int y) {
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=y;i++) if( !one_Step(x,y-i) ) vis[sg[x][y-i]] = 1;
    for(int i=1;i<=x;i++) if( !one_Step(x-i,y) ) vis[sg[x-i][y]] = 1;
    for(int i=1,mi=std::min(x,y);i<=mi;i++) if( !one_Step(x-i,y-i) ) vis[sg[x-i][y-i]] = 1;
}

int main() {
    static int t,n,su,flag;
    for(int i=0;i<100;i++) for(int j=0;j<100;j++) if( !one_Step(i,j) ) mark_Point(i,j) , sg[i][j] = calc_Mex();
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&n) , su = flag = 0;
        for(int i=1,x,y;i<=n;i++) {
            scanf("%d%d",&x,&y);
            if( one_Step(x,y) ) flag = 1;
            else su ^= sg[x][y];
        }
        puts(flag||su?"^o^":"T_T");
    }
    return 0;
}


