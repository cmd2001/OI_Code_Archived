#include<iostream>  
#include<cstdio>  
#include<string>  
#include<cstring>  
#include<vector>  
#include<cmath>  
#include<queue>  
#include<stack>  
#include<map>  
#include<set>  
#include<algorithm>  
using namespace std;  
const int maxn=1100;  
int N;  
int g[maxn][maxn];  
int nex[maxn];  
bool expend(int st)  
{  
    for(int i=0;i<N;i++)nex[i]=-1;  
    int head=st,tail=head;  
    for(int i=0;i<N;i++)  
    {  
        if(i==st)continue;  
        if(g[i][head])nex[i]=head,head=i;  
        else  
        {  
            int x=head,y=nex[head];  
            while(y!=-1&&g[y][i])  
            {  
                x=y;  
                y=nex[y];  
            }  
            nex[x]=i;  
            nex[i]=y;  
            if(y==-1)tail=i;  
        }  
    }  
    if(g[tail][head])  
    {  
        nex[tail]=head;  
        return true;  
    }  
    return false;  
}  
bool solve()  
{  
    for(int i=0;i<N;i++)  
        if(expend(i))return true;  
    return false;  
}  
int main()  
{  
    while(scanf("%d",&N)!=EOF,N)  
    {  
        for(int i=0;i<N;i++)  
            for(int j=0;j<N;j++)  
                scanf("%d",&g[i][j]);  
        //if(N==1){printf("0\n");continue;}  
        if(N==2||!solve())printf("1\n");
        else printf("%d\n",0);
        for(int i=0,j=0;i<N;i++,j=nex[j])  
            printf("%d%c",j+1,i==N-1?'\n':' ');  
    }  
    return 0;  
}  
