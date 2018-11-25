#include<cstdio>
using namespace std;
const int maxn=2018;

long long int t1,t2,ans;
int a,b,c,d;

inline void ope(int x,int oper,long long int& ans)
{
    int m=x%2017;
    ans+=(x/2017)*oper;
    //if(m!=0) ans-=oper;
}

int main()
{
    scanf("%d%d%d%d",&a,&b,&c,&d);
    ope(b,1,t1);
    ope(a-1,-1,t1);
    ans+=t1*(d-c+1);
    ope(d,1,t2);
    ope(c-1,-1,t2);
    ans+=t2*(b-a+1);

    //printf("t1= %lld t2= %lld\n",t1,t2);

    ans-=t1*t2;

    printf("%lld\n",ans);

    return 0;
}


