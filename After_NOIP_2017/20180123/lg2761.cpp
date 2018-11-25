#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ext/pb_ds/priority_queue.hpp>
#define uint unsigned int
#define debug cout
using namespace std;
using namespace __gnu_pbds;
const int maxn=1.1e6+1e2,maxm=1e2+1e1;
const int inf=0x3f3f3f3f;

struct Node {
    int dis;
    uint pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis != b.dis ? a.dis > b.dis : a.pos < b.pos;
    }
};
__gnu_pbds::priority_queue<Node,less<Node>,pairing_heap_tag> heap;
__gnu_pbds::priority_queue<Node,less<Node>,pairing_heap_tag>::point_iterator it[maxn];
uint b1[maxm],b2[maxm],f1[maxm],f2[maxm],full;
int dis[maxn],cst[maxm];
int n,m;

inline bool trans(uint now,uint& ret,int id) {
    if(  (now&b1[id]) != b1[id] || ( now&b2[id] ) ) return 0;
    ret = ( now & ( full - f1[id] ) ) | f2[id];
    return 1;
}
inline void dji() {
    memset(dis,0x3f,sizeof(dis)) , dis[full] = 0;
    it[full] = heap.push((Node){dis[full],full});
    while( heap.size() && dis[0] == inf ) {
        const uint pos = heap.top().pos; heap.pop(); it[pos] = NULL;
        uint tar;
        for(int i=1;i<=m;i++)
            if( trans(pos,tar,i) && dis[tar] > dis[pos] + cst[i] ) {
                //if( pos == full ) debug<<"i = "<<i<<endl;
                //debug<<"tar = "<<tar<<endl;
                dis[tar] = dis[pos] + cst[i];
                if( it[tar] != NULL ) heap.modify(it[tar],(Node){dis[tar],tar});
                else it[tar] = heap.push((Node){dis[tar],tar});
            } 
    }
}

char in[maxm];
inline void explain(uint &add,uint &minus) {
    for(int i=0;i<n;i++)
        if( in[i] == '+' ) add |= ( 1u << i );
        else if( in[i] == '-' ) minus |= ( 1u << i );
}
int main() {
    scanf("%d%d",&n,&m); full = ( 1u << n ) - 1u;
    for(int i=1;i<=m;i++) {
        scanf("%d%s",cst+i,in);
        explain(b1[i],b2[i]);
        scanf("%s",in);
        explain(f2[i],f1[i]);
    }
    
    dji();
    
    //for(int i=full;~i;i--) debug<<dis[i]<<" ";debug<<endl;
    if( *dis == inf ) puts("0");
    else printf("%d\n",*dis);
    
    return 0;
}
