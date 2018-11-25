#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int f[200000][20];
int m;
int mod;
void dp(int i,int j,int state,int nex)  
{  
    if (j==4)  
    {  
        f[i+1][nex]+=f[i][state];  
        f[i+1][nex]%=mod;  
        return;  
    }  
    if (((1<<j)&state)>0)  
        dp(i,j+1,state,nex);  
    if (((1<<j)&state)==0)  
        dp(i,j+1,state,nex|(1<<j));  
    if (j+1<4 && ((1<<j)&state)==0 && ((1<<(j+1))&state)==0)  
        dp(i,j+2,state,nex);  
    return;  
}  
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	while(cin>>m>>mod&&m)
	{
		memset(f,0,sizeof(f));
		f[1][0]=1;
		for (int i=1;i<=m;i++)  
	    {  
	        for (int j=0;j<16;j++)  
	        if (f[i][j])  
	        {  
	            dp(i,0,j,0);  
	        }  
	    }  
	    cout<<f[m+1][0]<<endl;
	}
	fclose(stdin);
	fclose(stdout);
    return 0;
}

