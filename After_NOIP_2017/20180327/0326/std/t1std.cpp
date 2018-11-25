//可持久化线段树合并维护SAM的pre树中的right数组
//复杂度nlogn
#include<bits/stdc++.h>
#define debug cout
#define N 200005
using namespace std;
int n;
//---------xds--------------
const int L=0,R=1;
struct xds{
    int son[2],size;
}a[N*20*2];int xdscnt;
void insert(int &k,int l,int r,int x){
    int t=++xdscnt;a[t]=a[k];a[t].size++;k=t;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(mid>=x) insert(a[k].son[L],l,mid,x);
    else insert(a[k].son[R],mid+1,r,x);
}
void merge(int &x,int y){
    if(a[x].size==0) {x=y;return;}
    if(a[y].size==0) {return;}
    int t=++xdscnt;a[t].size=a[x].size+a[y].size;a[t].son[L]=a[x].son[L];a[t].son[R]=a[x].son[R];x=t;
    merge(a[x].son[L],a[y].son[L]);merge(a[x].son[R],a[y].son[R]);
}
int query(int k,int l,int r,int ll,int rr){
    if(l>r) puts("WA");
    if(k==0) return 0;
    if(l==ll&&r==rr) return a[k].size;
    int mid=(ll+rr)>>1;
    if(l>mid) return query(a[k].son[R],l,r,mid+1,rr);
    else if(r<=mid) return query(a[k].son[L],l,r,ll,mid);
    else return query(a[k].son[L],l,mid,ll,mid)+query(a[k].son[R],mid+1,r,mid+1,rr);
}
//----------sam-------------
int len[N*2],ne[N*2][27],pre[N*2],rit[N*2],pos[N*2];
int root,cnt;
char S[N];
void build(){
    int last,now,p,k,ch,lca;
    root=last=++cnt;
    for(int i=1;i<=n;i++){
        p=last;last=now=++cnt;ch=S[i]-'a';len[now]=i;pos[now]=rit[now]=i;
        while(p&&ne[p][ch]==0) ne[p][ch]=now,p=pre[p];
        if(p){
            k=ne[p][ch];
            if(len[k]!=len[p]+1){
                len[lca=++cnt]=len[p]+1;pre[lca]=pre[k];
                memcpy(ne[lca],ne[k],sizeof(ne[k]));
                pre[k]=pre[now]=lca;pos[lca]=pos[k];
                while(p&&ne[p][ch]==k) ne[p][ch]=lca,p=pre[p];
            }else pre[now]=k;
        }else pre[now]=root;
    }
}
//--------------------------
int tp[N*2],buf[N*2],mrt[N*2],best[N*2],ans[N*2],lenmn[N*2];
 
//标号，双关键字，第一关键字长度，第二关键字原串中的出现位置 
//tp[i]表示的是标号为i的那个节点
  
void px(){
    for(int i=1;i<=cnt;i++) buf[len[i]]++;
    for(int i=1;i<=n;i++) buf[i]+=buf[i-1];
    for(int i=cnt;i>=1;i--) tp[buf[len[i]]--]=i;
}
  
void build_xds(){
    //对于一颗线段树保存了主链以及parent树上的儿子的rit集合 
    for(int i=cnt;i>=2;i--){
        int k=tp[i],t=0;
        if(rit[k]!=0) insert(t,1,n,rit[k]), merge(mrt[k],t);
        merge(mrt[pre[k]],mrt[k]);
    }
}
 
void getans(){
    for(int i=2;i<=cnt;i++) lenmn[i]=len[pre[i]]+1; // 节点最小长度
    best[1] = 1;
    for(int i = 2; i <= cnt; i++){
        int k = tp[i];
        if(pre[k] == 1) ans[k] = 1, best[k] = k;
        else {
            int b = best[pre[k]];
            if(query(mrt[b], pos[k] - len[k] + 1 + len[b] - 1, pos[k] - 1, 1, n) > 0) 
                ans[k] = ans[b] + 1, best[k] = k;
            else best[k] = b;
        }
    }
}
 
//--------------------------
int main(){
    scanf("%s",S+1);
    n=strlen(S+1);
    build();
    px();
    build_xds();
    getans();
    int ansout=0;
    for(int i=1;i<=cnt;i++) ansout=max(ansout,ans[i]);
    cout<<ansout<<endl;
    return 0;
}
