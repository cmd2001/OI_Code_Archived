#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+1e2;

char in[maxn][maxn];
int step[maxn][maxn];

int n,m,x,y;
inline void move(char c,int& x,int &y) {
    if( c == 'N') --x;
    else if( c == 'S' ) ++x;
    else if( c == 'E' ) ++y;
    else if( c == 'W' ) --y;
}
inline bool judge(int x,int y) {
    return x > 0 && x <= n && y > 0 && y <= m;
}

inline void getans(int x,int y) {
    int now = 0;
    while( judge( x , y ) ) {
        ++now;
        if( step[x][y] ) {
            printf("%d %d\n",step[x][y]-1,now-step[x][y]);
            return;
        }
        step[x][y] = now;
        move(in[x][y],x,y);
    }
    printf("%d\n",now);
}

int main() {
    //memset(step,-1,sizeof(step));
    scanf("%d%d%d",&n,&m,&y);
    x = 1;
    for(int i=1;i<=n;i++)
        scanf("%s",in[i]+1);
    getans(x,y);
    
    return 0;
}