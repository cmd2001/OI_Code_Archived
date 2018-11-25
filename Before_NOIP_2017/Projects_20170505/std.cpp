#include<cstdio>
#define mod 1000000000
struct _Main{
_Main(){
    int i;
    scanf("%lld",&n);
    ini();
    printf("%d",newdfs(0,n));
}

inline long long lb(long long x){
    return x&(-x);
}

long long mem[67][65];//以2^i为结尾，搜2^j及以上位数的方案数的搜索结果 
long long dp[67][66][67];//以2^i为开头,2^k为结尾,和为2^j的方案数 
int ini(){
    //缩小枚举范围 
    long long maxbit=62;
    for(;!((1LL<<maxbit)&n);maxbit--);

    int i,j,k,l,m,r;
    dp[0][0][0]=1;
    for(j=1;j<=maxbit;j++){
        //初始值 
        dp[j][j][j]=1;
        for(i=0;i<j;i++){
            for(k=i;k<j;k++){
                //递推
                for(l=i;l<=k;l++){
                    for(m=l;m<=k;m++){    
                        dp[i][j][k]+=dp[i][j-1][l]*dp[m][j-1][k];
                        dp[i][j][k]%=mod;    
                    }
                }
            }
        }
    }
}

int newdfs(long long last,long long rem){

    
    if(rem==0)return 1;
    long long i,j=0,k=0;
    long long ans=0;
    long long sum1=0,sum=0;
    long long i2=0;
    //找到最低位 
    for(i=last;!((1LL<<i)&lb(rem));i++);
    rem=rem-lb(rem);

    
    if(rem){//找出删除该位之后剩余位的最低位 用于记忆化 
        for(i2=i+1;!((long long)(1LL<<i2)&lb(rem));i2++);
    }
    
    for(k=last;k<=i;k++){//枚举结尾
     
        //记忆化搜索 剩余位的组合方案 k表示以k为最小开头，i2表示剩余最低位为2^i2 
        if(!mem[k][i2]){
            ans=newdfs(k,rem);
            mem[k][i2]=ans+1;
            printf("mem[%d][%d]=%lld\n",i2,k,mem[k][i2]);
        }else ans=mem[k][i2]-1;
        
        //当前位的组合方案  枚举开头 
        for(j=last;j<=k;j++){
            sum+=dp[j][i][k];
            sum%=mod;
        }
        //两部分相乘加到总和中 
        sum1=(sum1+ans*sum)%mod;
        sum=0;
    }

    return sum1;
    
}
long long n;
}ztime;int main(){}
