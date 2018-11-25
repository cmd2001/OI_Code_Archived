#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
using namespace std;
const int maxn=1e5+1e2,maxm=5e4+1e2;

int fail[maxn];
map<int,int> ch[maxn];
vector<int> eds[maxn],in[maxm],resp,resc;
int ansp[maxm],ansc[maxm];
bool vis[maxn],mrk[maxm];
int root,cnt;
int tp[maxn],tl;

inline void insert(int* s,int len,int id) {
    int now = root;
    for(int i=1;i<=len;i++) {
        const int t = s[i];
        if( ! ch[now].count(t) )
            ch[now][t] = ++cnt;
        now = ch[now][t];
    }
    eds[now].push_back(id);
}
inline void buildfail() {
    queue<int> q;
    fail[root] = root;
    for(int i=-1;i<=10000;i++)
        if( ch[root].count(i) ) {
            fail[ch[root][i]] = root;
            q.push(ch[root][i]);
        }
        else
            ch[root][i] = root;
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(map<int,int>::iterator it=ch[pos].begin();it!=ch[pos].end();++it) {
            const int t = it->first , tar = it->second;
            int now = fail[pos];
            while( !ch[now].count(t) )
                now = fail[now];
            fail[tar] = ch[now][t];
            q.push(tar);
        }
    }
}
inline void update(int pos,int id) { // pos is a node in ACautomatic
    for(;pos!=1&&!vis[pos];pos=fail[pos]) {
        vis[pos] = 1;
        resp.push_back(pos);
        for(unsigned i=0;i<eds[pos].size();i++) {
            const int ca = eds[pos][i];
            if( !mrk[ca] ) {
                mrk[ca] = 1;
                ++ansc[ca];
                ++ansp[id];
                resc.push_back(ca);
            }
        }
    }
}
inline void reset() {
    for(unsigned i=0;i<resp.size();i++)
        vis[resp[i]] = 0;
    for(unsigned i=0;i<resc.size();i++)
        mrk[resc[i]] = 0;
    resp.clear(); resc.clear();
}
inline void getans(vector<int> s,int id) {
    reset();
    int now = root;
    for(unsigned i=0;i<s.size();i++) {
        while( !ch[now].count(s[i]) )
            now = fail[now];
        now = ch[now][s[i]];
        update(now,id);
    }
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,l;i<=n;i++) {
        scanf("%d",&l);
        for(int j=1,x;j<=l;j++) {
            scanf("%d",&x);
            in[i].push_back(x);
        }
        in[i].push_back(-1);
        scanf("%d",&l);
        for(int j=1,x;j<=l;j++) {
            scanf("%d",&x);
            in[i].push_back(x);
        }
    }
    
    root = cnt = 1;
    for(int i=1;i<=m;i++) {
        scanf("%d",&tl);
        for(int j=1;j<=tl;j++)
            scanf("%d",tp+j);
        insert(tp,tl,i);
    }
    buildfail();
    for(int i=1;i<=n;i++)
        getans(in[i],i);
    
    for(int i=1;i<=m;i++)
        printf("%d\n",ansc[i]);
    for(int j=1;j<=n;j++) {
        printf("%d",ansp[j]);
        if( j != n )
            putchar(' ');
    }
    
    return 0;
}
