#include<bits/stdc++.h>  
using namespace std;    int n,k;  
int main(){  
    scanf("%d%d",&n,&k);  
    printf("%d",n==1?1:(min(k,n-k+1)<<1));  
    return 0;  
}  
