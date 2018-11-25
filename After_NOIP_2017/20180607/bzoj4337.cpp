#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int maxn=5e1+1e1;
const int inf=0x3f3f3f3f;

int m,n;

struct Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
    int siz[maxn],mxs[maxn];
    inline void coredge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void findrt(int pos,int fa,int &rt,int &rt2) {
        siz[pos] = 1 , mxs[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) findrt(t[at],pos,rt,rt2) , siz[pos] += siz[t[at]] , mxs[pos] = max( mxs[pos] , siz[t[at]] );
        mxs[pos] = max( mxs[pos] , n - siz[pos] );
        if( mxs[pos] < mxs[rt] ) rt = pos , rt2 = -1;
        else if( mxs[pos] == mxs[rt] ) rt2 = pos;
    }
    inline string dfs(int pos,int fa) {
        string ret = "a";
        vector<string> ss;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) ss.push_back(dfs(t[at],pos));
        if( ss.size() ) {
            sort(ss.begin(),ss.end());
            for(unsigned i=0;i<ss.size();i++) ret = ret + ss[i];
        }
        return ret = ret + "b";
    }
    inline string solve() {
        int rt = 0 , rt2 = -1;
        *mxs = inf , findrt(1,-1,rt,rt2);
        if( ~rt2 ) return min( dfs(rt,-1) , dfs(rt2,-1) );
        else return dfs(rt,-1);
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , cnt = 0;
    }
}ntr;

map<string,int> mp;

int main() {
    scanf("%d",&m);
    for(int i=1;i<=m;i++) {
        scanf("%d",&n) , ntr.reset();
        for(int i=1,a;i<=n;i++) {
            scanf("%d",&a);
            if(a) ntr.addedge(a,i);
        }
        string cur = ntr.solve();
        if( mp.find(cur) == mp.end() ) mp[cur] = i;
        printf("%d\n",mp[cur]);
    }
    return 0;
}
