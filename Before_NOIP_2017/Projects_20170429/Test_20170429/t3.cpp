#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define debug cout
//Just a hopeless brute force solution by Cmd2001
//OrzFY_OrzFY_OrzFY
//OrzFY_OrzFY_OrzFY
//OrzFY_OrzFY_OrzFY
using namespace std;
const int maxn=1e5+1e2;
long long int org[maxn];
int n,m,i,j,s,e,tmp,t,cal;
long long int sum;
char cmd;
void update(int pos,int x)
{
    while(pos<=n)
    {
        org[pos]+=x;
        pos+=lowbit(pos);
    }
}
long long int query(int pos)
{
    long long int ret=0;
    while(pos)
    {
        ret+=org[pos];
        pos-=lowbit(pos);
    }
    return ret;
}

inline int getint()
{
    int ret=0,fix=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') fix=-1;ch=getchar();}
    while('0'<=ch&&ch<='9')
    {
        ret=ret*10+ch-'0';
        ch=getchar();
    }
    return ret*fix;
}
inline char getcmd()
{
    char ch=getchar();
    while(ch=='\n'||ch==' ') ch=getchar();
    return ch;
}

long long int gcd(long long int a,long long int b)
{
    while(a%b)
    {
        a%=b;
        a^=b^=a^=b;
    }
    return b;
}

int main()
{
    t=0,n=getint(),m=getint();
    for(i=1;i<=m;i++)
    {
        cmd=getcmd();
        if(cmd=='C')
        {
            s=getint(),e=getint(),tmp=getint();
            update(s,tmp);
            update(e,-tmp);
        }
        else if(cmd=='Q')
        {
            s=getint(),e=getint();
            sum=0,tmp=0;
            for(j=s;j<e;j++)
            {
                sum+=query(j)*(j-s+1)*(e-j);
            }
            cal=e-s,tmp=0;
            for(j=1;j<=cal;j++) tmp+=j;
            cal=gcd(sum,tmp);
            sum/=cal,tmp/=cal;
            printf("%I64d/%d\n",sum,tmp);
        }
    }
    //while(1);
    return 0;
}
//OrzzrtOrzzrtOrzzrt
//OrzzrtOrzzrtOrzzrt
//OrzzrtOrzzrtOrzzrt
//OrzzrtOrzzrtOrzzrt
//OrzzrtOrzzrtOrzzrt
//OrzzrtOrzzrtOrzzrt

