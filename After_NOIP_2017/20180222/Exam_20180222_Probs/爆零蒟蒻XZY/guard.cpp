#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxm=4e4+1e2,maxe=55;
const int inf=0x3f3f3f3f;

int k[maxn],sum[maxn],n,full,mip,ans;
int st,ed,len;
bool vis[maxn];

struct Elevator {
	int h,x,y;
	friend bool operator < (const Elevator &a,const Elevator &b) {
		if( a.h != b.h ) return a.h < b.h;
		if( a.x != b.x ) return a.x < b.x;
		return a.y < b.y;
	}
	friend bool operator == (const Elevator &a,const Elevator &b) {
		return a.h == b.h && a.x == b.x && a.y == b.y;
	}
};
vector<Elevator> v;

namespace Flow {
	int s[maxn],t[maxm<<1],nxt[maxm<<1],f[maxm<<1],dep[maxn],cnt=1;
	
	inline void coredge(int from,int to,int flow) {
		t[++cnt] = to , f[cnt] = flow ,
		nxt[cnt] = s[from] , s[from] = cnt;
	}
	inline void singledge(int from,int to,int flow) {
		coredge(from,to,flow) , coredge(to,from,0);
	}
	inline bool bfs() {
		memset(dep,-1,sizeof(dep)) , dep[st] = 0;
		queue<int> q; q.push(st);
		while( q.size() ) {
			const int pos = q.front(); q.pop();
			for(int at=s[pos];at;at=nxt[at]) {
				if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
			}
		}
		return ~dep[ed];
	}
	inline int dfs(int pos,int flow) {
		if( pos == ed ) return flow;
		int ret = 0 , now = 0;
		for(int at=s[pos];at;at=nxt[at])
			if( f[at] && dep[t[at]] > dep[pos] ) {
				now = dfs(t[at],min(flow,f[at]));
				ret += now , flow -= now ,
				f[at] -= now , f[at^1] += now;
				if( !flow ) return ret;
			}
		if( !ret ) dep[pos] = -1;
		return ret;
	}
	inline int dinic() {
		int ret = 0 , now = 0;
		while( bfs() )
			while( ( now = dfs(st,inf) ) ) ret += now;
		return ret;
	}
	inline void reset() {
	    memset(s,0,sizeof(s)) , cnt = 1;
	}
}

inline int countbit(int x) {
    #define lowbit(x) (x&-x)
    int ret = 0;
    while( x ) ++ret , x -= lowbit(x);
    return ret;
}
inline int covdep(int dep,int pos) {
	return sum[dep-1] + pos;
}

inline int rebuild(int sta) {
    Flow::reset() , memset(vis,0,sizeof(vis));
    int ret = 0;
    for(int i=0;i<k[mip];i++) if( ! ( sta & ( 1 << i ) ) ) vis[covdep(mip,i+1)] = 1;
    for(int i=0;i<len;i++) {
        const int h = v[i].h , th = h != n ? h + 1 : 1;
        if( h == mip) {
            if( ( 1 << ( v[i].x - 1 ) ) & sta ) vis[covdep(th,v[i].y)] = 1;
        }
        else if( th == mip ) {
            if( ( 1 << ( v[i].y - 1 ) ) & sta ) vis[covdep(h,v[i].x)] = 1;
        }else {
            if( ( h > mip && ( ( h - mip ) & 1 ) ) || ( h < mip && ! ( ( mip - h ) & 1 ) ) )
                Flow::singledge(covdep(h,v[i].x),covdep(th,v[i].y),1);
            else Flow::singledge(covdep(th,v[i].y),covdep(h,v[i].x),1);
        }
    }
    for(int i=1;i<=n;i++) {
        if( ( i > mip && ( ( i - mip ) & 1 ) ) || ( i < mip && !( ( mip - i ) & 1 ) ) ) {
            for(int j=1;j<=k[i];j++)
                if( !vis[covdep(i,j)] ) Flow::singledge(st,covdep(i,j),1);
        } else if( i != mip ) {
            for(int j=1;j<=k[i];j++)
                if( !vis[covdep(i,j)] ) Flow::singledge(covdep(i,j),ed,1);
        }
    }
    for(int i=1;i<=full;i++) ret += !vis[i];
    ret -= Flow::dinic();
    return ret;
}
inline void getansodd() {
    int fs = ( 1 << k[mip] );
    for(int i=0;i<fs;i++) ans = max( ans , rebuild(i) );
}
inline void getanseven() {
    for(int i=0;i<len;i++) {
		const int x = covdep(v[i].h,v[i].x);
		const int y = covdep(v[i].h!=n?v[i].h+1:1,v[i].y);
		if( v[i].h & 1 ) Flow::singledge(x,y,1);
		else Flow::singledge(y,x,1);
	}
	for(int i=1;i<=n;i++) {
		if( i & 1 ) {
			for(int j=1;j<=k[i];j++)
				Flow::singledge( st , covdep(i,j) , 1 );
		} else {
			for(int j=1;j<=k[i];j++)
				Flow::singledge( covdep(i,j) , ed , 1 );
		}
	}
	ans = full - Flow::dinic();
}

inline void pre() {
	sort(v.begin(),v.end());
	len = unique(v.begin(),v.end()) - v.begin();
	for(int i=1;i<=n;i++) sum[i] = sum[i-1] + k[i];
	full = sum[n] , st = full + 1 , ed = full + 2;
	*k = inf;
	for(int i=1;i<=n;i++) if( k[i] < k[mip] ) mip = i;
}

int main() {
    freopen("guard.in","r",stdin);
    freopen("guard.out","w",stdout);
	static int h,x,y;
	scanf("%d",&n);
	int t = 0;
	while( scanf("%d%d%d",&x,&y,&h) == 3 ) {
		v.push_back((Elevator){h,x,y});
		k[h] = max( k[h] , x ) , k[h!=n?h+1:1] = max( k[h!=n?h+1:1] , y );
		++t;
	}
	pre();
	if( n & 1 ) getansodd();
	else getanseven();
	printf("%d\n",ans);
	fclose(stdout);
	return 0;
}

