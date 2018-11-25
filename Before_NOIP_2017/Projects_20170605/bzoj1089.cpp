#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=5e4+1e2;
struct NUM
{
    int dat[maxn],len;
    NUM(){memset(dat,0,sizeof(dat));len=0;}
    int& operator [] (const int &x)
    {
        return dat[x];
    }
    friend NUM operator + (const NUM &a,const NUM &b)
    {
        NUM ret=a;
        ret.len=max(a.len,b.len);
        for(int i=1;i<=ret.len;i++)
        {
            ret.dat[i]+=b.dat[i];
            if(ret.dat[i]>=10) ret.dat[i+1]+=ret.dat[i]/10,ret.dat[i]%=10;
        }
        if(ret.dat[ret.len+1]) ret.len++;
        while((!ret.dat[ret.len])&&ret.len>0) ret.len--;
        return ret;
    }
    friend NUM operator - (const NUM &a,const NUM &b)
    {
        NUM ret=a;
        ret.len=a.len;
        for(int i=1;i<=ret.len;i++)
        {
            ret.dat[i]-=b.dat[i];
            if(ret.dat[i]<0) ret.dat[i]+=10,ret.dat[i+1]--;
        }
        while((!ret.dat[ret.len])&&ret.len>0) ret.len--;
        return ret;
    }
    friend NUM operator * (const NUM &a,const NUM &b)
    {
        NUM ret;
        ret.len=(a.len+1)*(b.len+1);
        for(int i=1;i<=a.len;i++)
            for(int j=1;j<=b.len;j++)
                ret.dat[i+j-1]+=a.dat[i]*b.dat[j];
        for(int i=1;i<=ret.len;i++)
            if(ret.dat[i]>=10) ret.dat[i+1]+=ret.dat[i]/10,ret.dat[i]%=10;
        while(!ret.dat[ret.len]&&ret.len>0) ret.len--;
        return ret;
    }
    void operator = (const int &x)
    {
        //debug<<"x="<<x<<endl;
        int t=x;
        while(t) len++,t/=10;
        t=x;
        for(int i=len;i>0;i--)
        {
            dat[i]=t%10;
            t/=10;
        }
    }
    void operator = (const char* in)
    {
        len=strlen(in);
        for(int i=1;i<=len;i++)
        {
            dat[i]=in[len-i]-'0';
        }
    }
    friend NUM operator ^ (const NUM &x,int tme)
    {
        NUM now=x,ret;
        ret=1;
        while(tme)
        {
            if(tme&1) ret=ret*now;
            now=now*now;
            tme>>=1;
        }
        return ret;
    }
    void display()
    {
        if(!len) putchar('0');
        for(int i=len;i>0;i--) putchar(dat[i]+'0');
        putchar('\n');
    }
}now,last,one;
int main()
{
    static int d,n;
    scanf("%d%d",&n,&d);
    if(d==0) puts("1"),exit(0);
    now=1;
    one=1;
    for(int i=1;i<=d;i++)
    {
        last=now;
        now=(last^n)+one;
    }
    (now-last).display();
    return 0;
}
