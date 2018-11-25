#include <iostream>

using namespace std;

int ans[50002][64];

bool used[50002][64];

bool le[64];

int N,M;

int waymax=0;

int dp(int i,int way)

{

if (!used[i][way])

{

 used[i][way] = true;

 for (int k=0;k<=waymax;k++)

   if ( (way&k) == 0 )

    if ( !le[(way|k)] )

        {

ans[i][way]+=dp(i+1,k);

ans[i][way]%=100003;

}

   }

return ans[i][way];

}

int main()

{

    cin>>N>>M;

int temp = 1;

for (int i=1;i<=N;i++)

{

waymax += temp;

temp*=2;

}

for (int i=0;i<=waymax;i++)

{

int temp = i;

int sum = 0;

int wei=0;

while (temp>0)

{

if (temp%2==0)

 sum++;

else

{

if (sum%2!=0)

 le[i] = true;

sum=0;

}

temp/=2;

wei++;

}

if ((N-wei)%2!=0)

 le[i] = true;

}

for (int i=0;i<=waymax;i++) 

 used[M+1][i]=true;

ans[M+1][0] = 1;

cout<<dp(1,0)<<endl;

return 0;

}
