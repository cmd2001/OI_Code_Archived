#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[101];
long long n,a[51];
long long re[10];
long long A[16],P[16]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
long long ANS;
void change(long long x,long long k)
{
    long long j=0;
    while(x!=1)
    {
        j++;
        while(x%P[j]==0)
        {
            x/=P[j];
            A[j]+=k;
        }
    }
}
void jc(long long x,long long k)
{
    long long i;
    for(i=2;i<=x;i++)
    change(i,k);
}
long long cal()
{
    long long i,j;
    long long ret=1;
    for(i=1;i<=15;i++)
    for(j=1;j<=A[i];j++)
    ret=ret*P[i];
    return ret;
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    long long i,j,k;
    for(i=1;i<=n;i++)
    {
        a[i]=s[i]-48;
        re[a[i]]++;
    }
    for(i=1;i<=n;i++)
    {
        for(j=0;j<a[i];j++)
        if(re[j])
        {
            re[j]--;
            memset(A,0,sizeof(A));
            jc(n-i,1);
            for(k=0;k<=9;k++)
            jc(re[k],-1);
            ANS+=cal();
            re[j]++;
        }
        re[a[i]]--;
    }
    printf("%lld",ANS);
}