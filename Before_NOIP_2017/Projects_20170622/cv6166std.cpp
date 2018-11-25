#include<iostream>

#include<cstdio>

#include<climits>

#include<algorithm>

#include<cstring>

#include<cmath>

using namespace std;

long long las1,las2,now,mod=14233333;

int main()

{

    int n,i;

    las2=1;las1=2;

    scanf("%d",&n);

    if(n==1){printf("1");return 0;}

    else if(n==2){printf("2");return 0;}

    for(i=3;i<=n;i++){

        now=(long long)las2*(i-1)+las1;

        now%=mod;las2=las1;las1=now;

    }

    printf("%lld",las1);

    return 0;

}
