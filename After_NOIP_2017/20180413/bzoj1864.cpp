#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=5e5+1e2;

char in[maxn];
int ch[maxn][3];
int f[maxn][3];
int cur,cnt;

inline void dfs1(int pos) {
    if( !ch[pos][0] ) f[pos][0] = 1 , f[pos][1] = f[pos][2] = 0;
    else if( ch[pos][0] == 1 ) {
        const int tar = ch[pos][1]; dfs1(tar);
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) if( i != j ) f[pos][i] = std::max( f[pos][i] , f[tar][j] + ( i == 0) );
    } else {
        const int x = ch[pos][1] , y = ch[pos][2]; dfs1(x) , dfs1(y);
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<3;k++)
            if( i != j && j != k && k != i )
                f[pos][i] = std::max( f[pos][i] , f[x][j] + f[y][k] + ( i == 0 ) );
    }
}
inline void dfs2(int pos) {
    if( !ch[pos][0] ) f[pos][0] = 1 , f[pos][1] = f[pos][2] = 0;
    else if( ch[pos][0] == 1 ) {
        const int tar = ch[pos][1]; dfs2(tar);
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) if( i != j ) f[pos][i] = std::min( f[pos][i] , f[tar][j] + ( i == 0) );
    } else {
        const int x = ch[pos][1] , y = ch[pos][2]; dfs2(x) , dfs2(y);
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<3;k++)
            if( i != j && j != k && k != i )
                f[pos][i] = std::min( f[pos][i] , f[x][j] + f[y][k] + ( i == 0 ) );
    }
}
inline void explain(int pos) {
    if( in[cur] == '0' ) ++cur;
    else if( in[cur] == '1' )
        ++cur , ch[pos][0] = 1 , explain(ch[pos][1]=++cnt) ;
    else if( in[cur] == '2' )
        ++cur , ch[pos][0] = 2 , explain(ch[pos][1]=++cnt) ,explain(ch[pos][2]=++cnt) ;
}

int main() {
    scanf("%s",in+1) , explain(cur=cnt=1);
    memset(f,0xef,sizeof(f)) , dfs1(1) , printf("%d ",std::max(f[1][0],std::max(f[1][1],f[1][2])));
    memset(f,0x3f,sizeof(f)) , dfs2(1) , printf("%d\n",std::min(f[1][0],std::min(f[1][1],f[1][2])));
    return 0;
}
