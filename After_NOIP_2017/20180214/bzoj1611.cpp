#include<cstdio>
#include<cstring>
#include<queue>
const int maxn=3e2+1e1;
const int inf=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

int in[maxn][maxn],tim[maxn][maxn];

inline int bfs() {
    if( in[0][0] == inf ) return 0;
    if( !in[0][0] ) return -1;
    std::queue<int> qx,qy;
    qx.push(0) , qy.push(0) , tim[0][0] = 0;
    while( qx.size() && qy.size() ) {
        const int x = qx.front() , y = qy.front(); qx.pop() , qy.pop();
        for(int i=0;i<4;i++) {
            const int tx = x + dx[i] , ty = y + dy[i];
            if( tx < 0 || ty < 0 || ( ~tim[tx][ty] ) || in[tx][ty] <= tim[x][y] + 1 ) continue;
            if( in[tx][ty] == inf ) return tim[x][y] + 1;
            tim[tx][ty] = tim[x][y] + 1 , qx.push(tx) , qy.push(ty);
        }
    }
    return -1;
}

int main() {
    static int n;
    scanf("%d",&n);
    memset(in,0x3f,sizeof(in)) , memset(tim,-1,sizeof(tim));
    for(int i=1,x,y,t;i<=n;i++) {
        scanf("%d%d%d",&x,&y,&t);
        in[x][y] = in[x][y] < t ? in[x][y] : t;
        for(int k=0;k<4;k++) {
            const int tx = x + dx[k] , ty = y + dy[k];
            if( tx < 0 || ty < 0 ) continue;
            in[tx][ty] = in[tx][ty] < t ? in[tx][ty] : t;
        }
    }
    printf("%d\n",bfs());
    return 0;
}
