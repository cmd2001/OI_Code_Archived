#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=20,pts=(1<<20)+10;
const int inf=0x3f3f3f3f;

int dis[pts],sou[pts],edg[pts],inq[pts];
int in[maxn][maxn];
int n,m,full; // m is statement

inline int trans(int sta,int way) {
    int ret = 0;
    for(int i=0;i<m;i++)
        if( sta & ( 1<<i ) ) {
            int t = in[way][i];
            ret |= ( 1 << t );
        }
    return ret;    
}

queue<int> q;

inline void core_spfa(int pos) {
    //debug<<"pos = "<<pos<<endl;
    for(int i=1;i<=n;i++) {
        int tar = trans(pos,i);
        //debug<<"tar = "<<tar<<endl;
        if( dis[tar] > dis[pos] + 1 ) {
            dis[tar] = dis[pos] + 1 , sou[tar] = pos , edg[tar] = i;
            if( !inq[tar] ) {
                q.push(tar);
                inq[tar] = 1;
            }
        }
    }
}

inline void spfa() {
    memset(dis,0x3f,sizeof(dis));
    dis[full] = 0;
    
    q.push(full);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        inq[pos] = 0; core_spfa(pos);
    }
    
}

inline void print() {
    static int stk[pts],top;
    if( dis[1] == inf ) {
        puts("impossible");
        //puts("*");
        return;
    }
    //debug<<"in print"<<endl;
    for(int i=1;i!=full;i=sou[i]) {
        //debug<<"i = "<<i<<endl;
        stk[++top] = edg[i];
    }
    while( top )
        printf("%x",stk[top--]-1);
    putchar('\n');
}

int main() {
    scanf("%d%d",&m,&n);
    full = ( 1 << m ) - 1;
    for(int i=0;i<m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&in[j][i]);
    
    spfa();
    print();
    
    return 0;
}