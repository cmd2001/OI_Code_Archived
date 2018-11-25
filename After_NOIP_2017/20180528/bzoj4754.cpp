#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#define debug cerr
typedef unsigned long long int ulli;
using namespace std;
using std::vector;
const int maxn=1e5+1e2;
const ulli base = 13 , ini = 23;
const int inf=0x3f3f3f3f;

std::set<ulli> app;
int n,ans=inf;

ulli pows[maxn],stp[maxn];
inline bool cmp(const int &a,const int &b) {
    return stp[a] < stp[b];
}

struct Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],deg[maxn],cnt,root;
    vector<int> sons[maxn];
    vector<ulli> prf[maxn];
    ulli h[maxn];

    inline void copystp(const vector<int> &v) {
        for(unsigned i=0;i<v.size();i++) stp[v[i]] = h[v[i]];
    }
    inline ulli gethsh(const vector<int> &sons,vector<ulli> &prf) {
        prf.resize(sons.size());
        for(unsigned i=0;i<sons.size();i++) prf[i] = ( i ? prf[i-1] : 0 ) * base + h[sons[i]];
        return *prf.rbegin();
    }
    inline ulli getseg(const vector<ulli> &prf,const int &st,const int &ed) {
        if( st == 0 ) return prf[ed];
        return prf[ed] - prf[st-1] * pows[ed-st+1];
    }
    inline ulli getspi(const vector<ulli> &hfa,const int &id) { // fa can't be a leaf node .
        if( id == 0 ) return getseg(hfa,1,hfa.size()-1);
        else if( id == (signed)hfa.size() - 1 ) return getseg(hfa,0,hfa.size()-2);
        else {
            ulli prv = getseg(hfa,0,id-1) , nxt = getseg(hfa,id+1,hfa.size()-1);
            return prv + nxt * pows[id];
        }
    }

    inline void coredge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        ++deg[a] , ++deg[b] , coredge(a,b) , coredge(b,a);
    }
    inline void dfs1(int pos,int fa) {
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) sons[pos].push_back(t[at]) , dfs1(t[at],pos);
        if( sons[pos].size() ) copystp(sons[pos]) , std::sort(sons[pos].begin(),sons[pos].end(),cmp) , h[pos] = gethsh(sons[pos],prf[pos]);
        else h[pos] = ini;
    }
    inline void dfs2(int pos,int fa,int fid) {
        if( ~fa ) {
            sons[pos].push_back(fa);
            ulli bk = h[fa] , oth = getspi(prf[fa],fid);
            h[fa] = oth , copystp(sons[pos]) , std::sort(sons[pos].begin(),sons[pos].end(),cmp) , h[pos] = gethsh(sons[pos],prf[pos]) , h[fa] = bk;
        } // now h is tbe hash of making pos root .
        for(unsigned i=0;i<sons[pos].size();i++) if( sons[pos][i] != fa ) dfs2(sons[pos][i],pos,i);
    }
    inline void dfs3(int pos,int fa,int fid) {
        if( deg[pos] == 1 ) { // pos is a leaf node .
            ulli tar = getspi(prf[fa],fid);
            if( app.find(tar) != app.end() ) ans = std::min( ans , pos );
        }
        for(unsigned i=0;i<sons[pos].size();i++) if( sons[pos][i] != fa ) dfs3(sons[pos][i],pos,i);
    }

    inline void workA() {
        for(int i=1;i<n;i++) if( deg[i] > 1 ) { root = i; break; }
        dfs1(root,-1) , dfs2(root,-1,-1);
        for(int i=1;i<n;i++) app.insert(h[i]);
    }
    inline void workB() {
        for(int i=1;i<=n;i++) if( deg[i] > 1 ) { root = i; break; }
        dfs1(root,-1) , dfs2(root,-1,-1) , dfs3(root,-1,-1);
    }
    inline void solve2() {
        for(int i=1;i<=n;i++) if( deg[i] == 1 ) ans = std::min( ans , i );
    }
}A,B;

int main() {
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , A.addedge(a,b);
    for(int i=1,a,b;i<=n;i++) scanf("%d%d",&a,&b) , B.addedge(a,b);
    if( n == 1 ) return puts("1") , 0;
    else if( n == 2 ) return B.solve2() , printf("%d\n",ans) , 0;
    ++n , *pows = 1; for(int i=1;i<=n;i++) pows[i] = pows[i-1] * base;
    A.workA() , B.workB() , printf("%d\n",ans);
    return 0;
}
