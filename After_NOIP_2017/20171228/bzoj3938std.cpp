#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<cmath>  
#include<iostream>  
#include<algorithm>  
#define maxn 100010  
#define N 600010  
  
using namespace std;  
  
struct yts  
{  
    int op,id;  
    long long k,tm;  
}q[N];  
  
long long tagk[4*N],tagb[4*N],Tagk[4*N],Tagb[4*N];  
int a[maxn];  
long long nowk[maxn],nowb[maxn],b[N],ans1,ans2;  
bool flag[4*N],Flag[4*N];  
int n,m,cnt,num;  
char s[20];  
  
double cross(long long k1,long long b1,long long k2,long long b2)  
{  
    return (b1-b2)/(1.0*(k2-k1));  
}  
  
void insert_mx(int i,int l,int r,int L,int R,long long B,long long K)  
{  
    int mid=(l+r)>>1;  
    if (L<=l && r<=R)  
    {  
        if (!flag[i]) tagk[i]=K,tagb[i]=B,flag[i]=1;  
        else  
        {  
            long long f1=B+K*b[l],f2=tagb[i]+tagk[i]*b[l],f3=B+K*b[r],f4=tagb[i]+tagk[i]*b[r];  
            if (f1<=f2 && f3<=f4) return;  
            if (f1>=f2 && f3>=f4) tagk[i]=K,tagb[i]=B;  
            else  
            {  
                double xx=cross(K,B,tagk[i],tagb[i]);  
                if (f1>=f2)  
                {  
                    if (xx<=b[mid]) insert_mx(i<<1,l,mid,L,R,B,K);  
                    else insert_mx(i<<1|1,mid+1,r,L,R,tagb[i],tagk[i]),tagb[i]=B,tagk[i]=K;  
                }  
                else  
                {  
                    if (xx>b[mid]) insert_mx(i<<1|1,mid+1,r,L,R,B,K);  
                    else insert_mx(i<<1,l,mid,L,R,tagb[i],tagk[i]),tagb[i]=B,tagk[i]=K;  
                }  
            }  
        }  
        return;  
    }     
    if (L<=mid) insert_mx(i<<1,l,mid,L,R,B,K);  
    if (mid<R) insert_mx(i<<1|1,mid+1,r,L,R,B,K);  
}  
  
void insert_mn(int i,int l,int r,int L,int R,long long B,long long K)  
{  
    int mid=(l+r)>>1;  
    if (L<=l && r<=R)  
    {  
        if (!Flag[i]) Tagk[i]=K,Tagb[i]=B,Flag[i]=1;  
        else  
        {  
            long long f1=B+K*b[l],f2=Tagb[i]+Tagk[i]*b[l],f3=B+K*b[r],f4=Tagb[i]+Tagk[i]*b[r];  
            if (f1>=f2 && f3>=f4) return;  
            if (f1<=f2 && f3<=f4) Tagk[i]=K,Tagb[i]=B;  
            else  
            {  
                double xx=cross(K,B,Tagk[i],Tagb[i]);  
                if (f1<=f2)  
                {  
                    if (xx<=b[mid]) insert_mn(i<<1,l,mid,L,R,B,K);  
                    else insert_mn(i<<1|1,mid+1,r,L,R,Tagb[i],Tagk[i]),Tagb[i]=B,Tagk[i]=K;  
                }  
                else  
                {  
                    if (xx>b[mid]) insert_mn(i<<1|1,mid+1,r,L,R,B,K);  
                    else insert_mn(i<<1,l,mid,L,R,Tagb[i],Tagk[i]),Tagb[i]=B,Tagk[i]=K;  
                }  
            }  
        }  
        return;  
    }     
    if (L<=mid) insert_mn(i<<1,l,mid,L,R,B,K);  
    if (mid<R) insert_mn(i<<1|1,mid+1,r,L,R,B,K);  
}  
  
void query_mx(int i,int l,int r,int id)  
{  
    if (flag[i]) ans1=max(ans1,tagb[i]+tagk[i]*b[id]);  
    if (l==r) return;  
    int mid=(l+r)>>1;  
    if (id<=mid) query_mx(i<<1,l,mid,id); else query_mx(i<<1|1,mid+1,r,id);  
}  
  
void query_mn(int i,int l,int r,int id)  
{  
    if (Flag[i]) ans2=min(ans2,Tagb[i]+Tagk[i]*b[id]);  
    if (l==r) return;  
    int mid=(l+r)>>1;  
    if (id<=mid) query_mn(i<<1,l,mid,id); else query_mn(i<<1|1,mid+1,r,id);  
}  
  
int main()  
{  

	freopen("dat.txt","r",stdin);
	freopen("std.txt","w",stdout);
    scanf("%d%d",&n,&m);  
    for (int i=1;i<=n;i++) scanf("%lld",&nowb[i]),nowk[i]=0,a[i]=0;  
    for (int i=1;i<=m;i++)  
    {  
        scanf("%lld",&q[i].tm);b[i]=q[i].tm;  
        scanf("%s",s+1);  
        if (s[1]=='c') scanf("%d%lld",&q[i].id,&q[i].k),q[i].op=1; else q[i].op=0;  
    }  
    num=m;b[++num]=0;  
    sort(b+1,b+num+1);  
    cnt=unique(b+1,b+num+1)-b-1;  
    for (int i=1;i<=m;i++)  
      if (q[i].op==1)   
      {  
        int x=q[i].id,lst=lower_bound(b+1,b+cnt+1,a[x])-b,now=lower_bound(b+1,b+cnt+1,q[i].tm)-b;  
        insert_mx(1,1,cnt,lst,now,nowb[x],nowk[x]);  
        insert_mn(1,1,cnt,lst,now,nowb[x],nowk[x]);  
        nowb[x]=nowb[x]+q[i].tm*(nowk[x]-q[i].k);nowk[x]=q[i].k;a[x]=q[i].tm;  
      }  
    for (int i=1;i<=n;i++)   
    {  
        int lst=lower_bound(b+1,b+cnt+1,a[i])-b;  
        insert_mx(1,1,cnt,lst,cnt,nowb[i],nowk[i]);  
        insert_mn(1,1,cnt,lst,cnt,nowb[i],nowk[i]);  
    }  
    for (int i=1;i<=m;i++)  
      if (q[i].op==0)  
      {  
        ans1=0;ans2=0;  
        int now=lower_bound(b+1,b+cnt+1,q[i].tm)-b;  
        query_mx(1,1,cnt,now);  
        query_mn(1,1,cnt,now);  
        printf("%lld\n",max(ans1,-ans2));  
      }  
    return 0;  
}  
