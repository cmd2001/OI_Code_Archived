#include<bits/stdc++.h>
using  namespace std;
int main()
{
    freopen("dp.txt","w",stdout);
    srand(time(NULL));
    int n=rand()%100000+1,m=rand()%10000+1;
    cout<<n<<endl;
    for(int i=1;i<=n;i++) cout<<rand()<<" ";
    cout<<endl<<m<<endl;
    for(int i=1,c,a,b,x;i<=m;i++)
    {
        c=rand()&1;
        if(c)
        {
            a=rand()%n+1;
            b=rand()%n+1;
            while(b<n) b=rand()%n+1;
            x=rand();
            printf("%d %d %d %d\n",c,a,b,x);
        }
        else
        {
            a=rand()%n+1;
            b=rand()%n+1;
            while(b<n) b=rand()%n+1;
            printf("2 %d %d\n",a,b);
        }
    }
}
