#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;
int lista[maxn],listb[maxn],cnta,cntb;
int cntla[maxn],cntlb[maxn];
int a,b,out;
void calc(int x,int *list,int *cntl,int &cnt)
{
    for(int i=2;i<=x;i++)
    {
        if(!(x%i)) list[++cnt]=i;
        while(!(x%i)) {x/=i;cntl[cnt]++;}
    }
    if(x!=1) {list[++cnt]=x;cntl[cnt]++;}
}
int main()
{
    scanf("%d%d",&a,&b);
    calc(a,lista,cntla,cnta);
    calc(b,listb,cntlb,cntb);
    int p=1;
    for(int i=1;i<=cnta;i++)
    {
        while(lista[i]>listb[p]&&p<=cntb) ++p;
        if(lista[i]==listb[p]) out+=min(cntla[i],cntlb[p]);
    }
    printf("%d\n",out);
    return 0;
}
