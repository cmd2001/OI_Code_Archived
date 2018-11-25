#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define pi acos(-1.0)
using namespace std;
inline void Edwina()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
}
const int mod=1e9+7,maxn=1e6+1,eps=1e-9,INF=0x3f3f3f3f;
char p[16][16];
int flg[maxn];
long long f[maxn];
int main()
{
	Edwina();
	int n,m,C=1;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%s",&p[i]);
    for(int i=1;i<(1<<n);i++)
    {
        flg[i] = 1;
        for(int j=0;j<n;j++)
        {
            if((1<<j)&i)
            for(int k=0;k<n;k++)
                if((1<<k)&i&&p[j][k]=='1')
                {
                    flg[i] = 0;
                    break;
                }
            if(!flg[i])
                break;
        }
    }
    f[0]=0;
    for(int i=1;i<(1<<n);i++)
    {
        f[i]=INF;
        for(int j=i;j;j=(j-1)&i)
            if(flg[j])f[i]=min(f[i],f[i^j]+1);
    }
    long long sum=0,cnt=1;
    for(int i=1;i<(1<<n);i++)
    {
        sum*=233;
        sum+=f[i]*sum;
    }
    printf("%u\n",(int)sum);
    fclose(stdin);
	fclose(stdout);
    return 0;
}

