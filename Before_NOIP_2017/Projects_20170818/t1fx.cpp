#include<bits/stdc++.h>
using namespace std;
const int maxn=20;

int n,mod;
struct martix
{
    lli dat[maxn][maxn];

    martix(int f=0)
    {
        memset(dat,0,sizeof(dat));
        if(f) for(int i=0;i<16;i++) dat[i][i]=1;
    }
    int* operator [] (const int &pos)
    {
        return dat[pos];
    }
    martix operator * (martix &a,martix &b)
    {
        martix ret;
        for(int i=0;i<16;i++)
            for(int j=0;j<16;j++)
                for(int k=0;k<16;k++)
                    ret[i][j]+=a[i][k]*b[k][j],
                    ret[i][j]%=mod;
        return ret;
    }
}

