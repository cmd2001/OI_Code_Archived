#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <string>  
#include <algorithm>  
#include <map>  
#include <vector>  
using namespace std;  
const int N = 1100;  
const int INF = 0x3f3f3f3f;  
  
struct Node  
{  
    int to;//终点  
    int cap; //容量  
    int rev;  //反向边  
};  
  
vector<Node> v[N];  
bool used[N];  
  
void add_Node(int from,int to,int cap)  //重边情况不影响  
{  
    v[from].push_back((Node){to,cap,v[to].size()});  
    v[to].push_back((Node){from,0,v[from].size()-1});  
}  
  
int dfs(int s,int t,int f)  
{  
    if(s==t)  
        return f;  
    used[s]=true;  
    for(int i=0;i<v[s].size();i++)  
    {  
        Node &tmp = v[s][i];  //注意  
        if(used[tmp.to]==false && tmp.cap>0)  
        {  
            int d=dfs(tmp.to,t,min(f,tmp.cap));  
            if(d>0)  
            {  
                tmp.cap-=d;  
                v[tmp.to][tmp.rev].cap+=d;  
                return d;  
            }  
        }  
    }  
    return 0;  
}  
  
int max_flow(int s,int t)  
{  
    int flow=0;  
    for(;;){  
        memset(used,false,sizeof(used));  
        int f=dfs(s,t,INF);  
        if(f==0)  
            return flow;  
        flow+=f;  
    }  
}  
int main()  
{  
    int n,m;  
    while(~scanf("%d%d",&n,&m))  
    {  
        memset(v,0,sizeof(v));  
        for(int i=0;i<n;i++)  
        {  
            int x,y,z;  
            scanf("%d%d%d",&x,&y,&z);  
            add_Node(x,y,z);  
        }  
        printf("%d\n",max_flow(1,m));  
    }  
}  
