#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
int data[7][8][7][8];
int in[7][8];
int ansx[7][8],ansy[7][8];
bool used[7][8];
int n;
void pre()
{
    for(int i=1;i<=5;i++)
    {
        for(int j=1;j<=6;j++)
        {
            data[i][j][i][j]=1;
            if(i>1) data[i][j][i-1][j]=1;
            if(j>1) data[i][j][i][j-1]=1;
            if(i<5) data[i][j][i+1][j]=1;
            if(j<6) data[i][j][i][j+1]=1;
        }
    }
}
void gauss()
{
    bool flag;
    int x,y;
    for(int i=1;i<=5;i++)
    {
        for(int j=1;j<=6;j++)
        {
            x=y=0,flag=1;
            for(int m=1;m<=5&&flag;m++) for(int n=1;n<=6&&flag;n++) if(data[m][n][i][j]&&!used[m][n]) x=m,y=n,used[m][n]=1,flag=0;
            //debug<<"x="<<x<<"y="<<y<<endl;
            ansx[i][j]=x,ansy[i][j]=y;
            for(int m=1;m<=5;m++)
            {
                for(int n=1;n<=6;n++)
                {
                    if((!(m==x&&n==y))&&data[m][n][i][j])
                    {
                        //debug<<"m="<<m<<"n="<<n<<"i="<<i<<"j="<<j<<endl;
                        for(int a=1;a<=5;a++)
                        {
                            for(int b=1;b<=6;b++)
                            {
                                data[m][n][a][b]^=data[x][y][a][b];
                            }
                        }
                        in[m][n]^=in[x][y];
                    }
                }
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int k=1;k<=n;k++)
    {
        memset(in,0,sizeof(in));
        memset(data,0,sizeof(data));
        memset(used,0,sizeof(used));
        for(int i=1;i<=5;i++) for(int j=1;j<=6;j++) scanf("%d",&in[i][j]);//,in[i][j]^=1;
        pre();
        gauss();
        printf("PUZZLE #%d\n",k);
        for(int i=1;i<=5;i++)
        {
            for(int j=1;j<=6;j++) printf("%d ",in[ansx[i][j]][ansy[i][j]]);
            printf("\n");
        }
    }
    return 0;
}

