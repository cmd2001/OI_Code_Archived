#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxl=(1<<10)-1;
const int INF=0x3F3F3F3F;

int dp[maxn][1048600];
int lst[10],sta[10],n;
bool in[maxn][5],now[10],vis[10];

inline int zip()
{
    int ret=0;
    for(int i=1;i<=5;i++)
    {
        ret|=sta[i]<<((i<<1)-2);
    }
    return ret;
}
inline void unzip(int x,int *scr) // lst is the last row's statement, sta is this row's statement.
{
    memset(scr,0,sizeof(scr));
    for(int i=1;i<=5;i++)
    {
        scr[i]=(x>>((i<<1)-2))&3;
    }
}

inline void getin()
{
    static char s[10];
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=5;j++)
        {
            in[i][j]=s[j]-'0';
        }
    }
}
int rec_fix(int x,int mi)
{
    vis[x]=1;
    if(!now[x]) return mi;
    sta[x]=min(mi,sta[x]);
    return sta[x]=min(sta[x],rec_fix(x+1,sta[x]));
}
inline void recolor()
{
	static bool vis[10];
	int l=1,r=10;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=5;i++) vis[sta[i]]=1;
	while(r>l)
	{
		if(!vis[r])
		{
			r--;
			continue;
		}
		vis[l]=1;
		for(int i=1;i<=5;i++) if(sta[i]==r) sta[i]=l;
		l++,r--;
	}
}
inline void fix()
{
	//debug<<"infix"<<endl;
	int cnt=4;
    memset(sta,0,sizeof(sta));
    for(int i=1;i<=5;i++)
	{
	    if(!now[i]) continue;
	    if(lst[i]) sta[i]=lst[i];
	    if(lst[i-1]) sta[i]=sta[i-1];
	    else sta[i]=++cnt;
	}
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=5;i++) if(!vis[i]) rec_fix(i,INF);
    recolor();
}
inline void dfs(int x,int i,int ans)
{
    if(x>5)
    {
        dp[i][zip()]=min(dp[i][zip()],ans);
        return;
    }
    if(now[x]) dfs(x+1,i,ans);
    else
    {
        now[x]=1;
        fix();
        dfs(x+1,i,ans+1);
        now[x]=0;
        fix();
        dfs(x+1,i,ans);
    }
}
inline bool judge(int x)
{
	static int num;
	unzip(x,sta);
	for(int i=1;i<=5;i++) if(sta[i]) num=sta[i];
	for(int i=1;i<=5;i++) if(sta[i]&&sta[i]!=num) return 0;
	return 1;
}
int main()
{
	static int ans=0x3fffffff;
    getin();
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=5;j++) now[j]=in[i][j];
        fix();
        debug<<"fixed"<<endl;
		for(int k=1;k<=5;k++) debug<<sta[k]<<" ";
    	debug<<endl;
        for(int k=0;k<=maxl;k++)
        {
            unzip(k,lst);
            for(int j=1;j<=5;j++) now[j]=in[i][j];
            dfs(1,i,dp[i-1][k]);
        }
    }
    for(int k=0;k<=maxl;k++)
    {
    	if(judge(k)) ans=min(ans,dp[n][k]);
    }
    debug<<ans<<endl;
    return 0;
}

