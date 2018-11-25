#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int u[maxn],v[maxn],len[maxn],ta[maxn],tb[maxn];
int n,used;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool dfs(int pos,int fa,int now,const int &tar,int* tim) {
    if( pos == tar ) return tim[pos] = now , 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa && dfs(t[at],pos,now+l[at],tar,tim) )
            return tim[pos] = now , 1;
    
    return 0; 
}
inline bool cross(int x,int y,int xx,int yy) {
    return x <= yy && xx <= y;
}
inline bool judge() {
    int sme = 0;
    for(int i=1;i<=n;i++) if( ~ta[i] && ~tb[i] ) sme += ( ta[i] == tb[i] );
    if( sme ) return sme > 1;
    for(int i=1;i<n;i++)
        if( ~ta[u[i]] && ~ta[v[i]] && ~tb[u[i]] && ~tb[v[i]] ) {
            if( ta[u[i]] - ta[v[i]] == tb[u[i]] - tb[v[i]] ) {
                if( abs(ta[u[i]] - tb[u[i]]) < len[i] ) return 1;
            } else if( cross(min(ta[u[i]],ta[v[i]]),max(ta[u[i]],ta[v[i]]),min(tb[u[i]],tb[v[i]]),max(tb[u[i]],tb[v[i]])) ) return 1;
        }
    return 0;
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1,l;i<n;i++) scanf("%d%d%d",u+i,v+i,len+i) , addedge(u[i],v[i],len[i]) , addedge(v[i],u[i],len[i]);
    for(int i=1,t,u,v,tt,uu,vv;i<=m;i++) {
        scanf("%d%d%d%d%d%d",&u,&v,&t,&uu,&vv,&tt) , memset(ta,-1,sizeof(ta)) , memset(tb,-1,sizeof(tb));
        dfs(u,-1,t,v,ta) , dfs(uu,-1,tt,vv,tb);
        puts(judge()?"YES":"NO");
    }
    return 0;
}
