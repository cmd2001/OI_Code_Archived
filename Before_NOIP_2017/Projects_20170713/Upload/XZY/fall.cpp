#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

struct node
{
    int y,sx,tx;
    friend bool operator < (const node &a,const node &b)
    {
        return a.y!=b.y?a.y>b.y:a.sx<b.sx;
    }
}z[maxn];

int n,x,y,t;

int main()
{
    freopen("fall.in","r",stdin);
    freopen("fall,out","w",stdout);

    scanf("%d%d",&x,&y);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&z[i].y,&z[i].sx,&z[i].tx);

    sort(z+1,z+1+n);

    for(int i=1;i<=n;i++)
    {
        while(y>z[i].y) y--,t++;
        if(y==z[i].y&&x>=z[i].sx&&x<=z[i].tx)
        {
            t+=5;
            x=z[i].tx;
        }
    }

    if(y) t+=y;

    printf("%d\n",t);

    fclose(stdin);
    fclose(stdout);

    return 0;
}



