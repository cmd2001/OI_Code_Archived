#include<bits/stdc++.h>
using namespace std;
const int maxn=25;

int ind[maxn],n;
double in[maxn][2],dis[maxn][maxn];

inline double getdis(int a,int b)
{
    static double dx,dy;
    dx=(in[a][1]-in[b][1]),dy=(in[a][2]-in[b][2]);
    return sqrt(dx*dx+dy*dy);
}
inline void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&in[i][1],&in[i][2]);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j]=getdis(i,j);
}

inline void rev(int a,int b)
{
    while(b>a)
    {
        swap(ind[a],ind[b]);
        a++,b--;
    }
}
inline double calc()
{
    for(int i=1;i<=n;i++) ind[i]=i;
    for(int i=1;i<=n;i++) swap(ind[i],ind[rand()%n+1]);

    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++)
    {
        if(dis[ind[i-1]][ind[i]]+dis[ind[j]][ind[j+1]]>dis[ind[i-1]][ind[j]]+dis[ind[i]][ind[j+1]])
            rev(i,j);
    }

    double ret=0;

    for(int i=1;i<n;i++) ret+=dis[ind[i]][ind[i+1]];

    return ret;
}


int main()
{
    static double ans=10000000000;
    init();
    for(int i=1;i<=2500;i++) ans=min(ans,calc());
    printf("%.2f\n",ans);
    return 0;
}


