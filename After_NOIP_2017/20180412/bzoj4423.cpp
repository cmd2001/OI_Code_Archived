#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2250100,maxe=1.5e3+1e1;

int id[maxe][maxe],iid,n,m,ans=1;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return x == fa[x] ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        return x == y ? 0 : ( fa[x] = y , 1  ) ;
    }
    inline void init() {
        for(int i=1;i<=iid;i++) fa[i] = i;
    }
}ufs;


int main() {
    static char o[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++) for(int j=1;j<n;j++) id[i][j] = ++iid;
    ufs.init();
    for(int i=1,x,y,a,b;i<=m;i++) {
        if( ans ) scanf("%d%d%s",&x,&y,o) , scanf("%*s%*s%*s");
        else scanf("%*s%*s%*s") , scanf("%d%d%s",&x,&y,o);
        if( *o == 'E' ) a = id[x][y-1] , b = id[x][y];
        else if( *o == 'N' ) a = id[x-1][y] , b = id[x][y];
        puts((ans=ufs.merge(a,b))?"TAK":"NIE");
    }
    return 0;
}
