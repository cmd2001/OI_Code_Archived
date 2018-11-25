#include<bits/stdc++.h>
#define bool unsigned char
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

lli h,ans;
lli dis[maxn];
int s[maxn],t[maxn<<4],nxt[maxn<<4],l[maxn<<4];
bool inq[maxn];
int a,b,c;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void spfa(int st) {
    memset(dis,0x7f,sizeof(dis)) , dis[st] = 0;
    queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
}
inline void getans() {
    --h;
    for(int i=0;i<c;i++)
        if( dis[i] <= h )
            ans += ( h - dis[i] ) / c + 1;
}

int main() {
    scanf("%lld%d%d%d",&h,&a,&b,&c);
    if( a > b ) swap(a,b);
    if( b > c ) swap(b,c);
    for(int i=0;i<c;i++)
        addedge(i,(i+a)%c,a) , addedge(i,(i+b)%c,b);
    spfa(0);
    getans();
    printf("%lld\n",ans);
    return 0;
}
