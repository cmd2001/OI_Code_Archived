#include<iostream>
int in[100010],c[3][100010],s[3],n,ans=3,i,j,t;int main(){std::cin>>n;for(i=1;i<=n;i++){std::cin>>t;for(j=0;j<3;j++) c[j][i]=c[j][i-1];++c[t][i],++s[t];}for(i=0;i<3;i++) s[i]>>=1;n>>=1;for(i=0;i<n;i++) if(c[0][i+n]-c[0][i]==s[0]&&c[1][i+n]-c[1][i]==s[1]&&c[2][i+n]-c[2][i]==s[2]){ans=i?2:1;break;}std::cout<<ans;}


