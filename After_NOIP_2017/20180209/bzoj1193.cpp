#include<cstdio>
#include<cstdlib>
const int d[5][5]={{0,3,2,3,2},{3,2,1,2,3},{2,1,4,3,2},{3,2,3,2,3},{2,3,2,3,4}};

int main() {
    static int xp,yp,xs,ys,dx,dy,ans;
    scanf("%d%d%d%d",&xp,&yp,&xs,&ys);
    dx = abs( xp - xs ) , dy = abs( yp - ys );
    while( dx > 4 || dy > 4 ) {
        if( dx < dy ) dx -= 1 , dy -= 2 , ++ans;
        else dx -= 2 , dy -= 1 , ++ans;
        dx = abs(dx) , dy = abs(dy);
    }
    ans += d[dx][dy];
    printf("%d\n",ans);
    return 0;
}
