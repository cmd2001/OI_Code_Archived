#include<bits/stdc++.h>
#define debug cout
using namespace std;
long long int n,k,r,p;
struct matx
{
    long long int dat[55][55];
    matx() {memset(dat,0,sizeof(dat));}
    friend matx operator * (const matx &a,const matx &b)
    {
        matx ret;
        for(int i=0;i<55;i++) for(int j=0;j<55;j++) for(int k=0;k<55;k++) ret.dat[i][j]+=a.dat[i][k]*b.dat[k][j],ret.dat[i][j]%=p;
        return ret;
    }
    long long int * operator [] (const int &i) {return dat[i];}

}ans,base;
inline void fastpow(matx b,matx &ret,long long tme)
{
    while(tme)
    {
        if(tme&1) ret=ret*b;
        b=b*b;
        tme>>=1;
    }
}
inline void init()
{
    for(int i=0;i<k;i++)
    {
        ans[i][i]++;
        base[i][i]++;
        base[(i-1+k)%k][i]++;
        //debug<<(i-1+k)%k<<endl;
    }
}

int main()
{
    /*freopen("data.in","r",stdin);
    freopen("my.txt","w",stdout);*/
    scanf("%lld%lld%lld%lld",&n,&p,&k,&r);
    //debug<<"k="<<k<<endl;
    init();
    /*debug<<"base="<<endl;
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<k;j++) debug<<base[i][j]<<" ";
        debug<<endl;
    }
    debug<<"ans="<<endl;
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<k;j++) debug<<ans[i][j]<<" ";
        debug<<endl;
    }*/
    fastpow(base,ans,n*k);
    printf("%lld\n",ans[r][0]);
    /*for(int i=0;i<k;i++)
    {
        for(int j=0;j<k;j++) debug<<ans[i][j]<<" ";
        debug<<endl;
    }*/
    return 0;
}


