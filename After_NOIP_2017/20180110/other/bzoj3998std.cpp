#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll long long 
using namespace std;
int T,n,K;
char ch[500005];
struct sam{
	int last,cnt;
	int a[1000005][26],fa[1000005],mx[1000005],val[1000005],sum[1000005];
	int v[500005],q[1000005];
	sam(){
		last=++cnt;
	}
	void extend(int c){
		int p=last,np=last=++cnt;
		mx[np]=mx[p]+1;val[np]=1;
		while(!a[p][c]&&p)a[p][c]=np,p=fa[p];
		if(!p)fa[np]=1;
		else 
		{
			int q=a[p][c];
			if(mx[p]+1==mx[q])fa[np]=q;
			else 
			{
				int nq=++cnt;mx[nq]=mx[p]+1;
				memcpy(a[nq],a[q],sizeof(a[q]));
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				while(a[p][c]==q)a[p][c]=nq,p=fa[p];
			}
		}
	}
	void pre(){
		for(int i=1;i<=cnt;i++)v[mx[i]]++;
		for(int i=1;i<=n;i++)v[i]+=v[i-1];
		for(int i=cnt;i;i--)q[v[mx[i]]--]=i;
		for(int i=cnt;i;i--)
		{
			int t=q[i];
			if(T==1)val[fa[t]]+=val[t];
			else val[t]=1;
		}
		val[1]=0;
		for(int i=cnt;i;i--)
		{
			int t=q[i];sum[t]=val[t];
			for(int j=0;j<26;j++)
				sum[t]+=sum[a[t][j]];
		}
        for(int i=1;i<=cnt;i++)
            printf("%d ",sum[i]);puts("");
	}
	void dfs(int x,int K){
		if(K<=val[x])return;
		K-=val[x];
		for(int i=0;i<26;i++)
			if(int t=a[x][i])
			{
				if(K<=sum[t])
				{
					putchar(i+'a');
					dfs(t,K);
					return;
				}
				K-=sum[t];
			}
	}
}sam;
int main()
{
	scanf("%s",ch+1);
	n=strlen(ch+1);
	scanf("%d%d",&T,&K);
	for(int i=1;i<=n;i++)
		sam.extend(ch[i]-'a');
	sam.pre();
	if(K>sam.sum[1])puts("-1");
	else sam.dfs(1,K);
    puts("");
	return 0;
}