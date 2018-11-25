#include<cstdio>
#include<cmath>
using namespace std;
inline int geta(int x,int y){	//x次y个蛋 最高 
	if(y==1) return x;
	if(x<=y) return (int)pow(2,x)-1;
	return geta(x-1,y-1)+geta(x-1,y)+1; //在某层 第一项为 碎了，答案>实际，第二项相反 
}
int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int f=1;
	while(geta(f,m)<n) f++;
	printf("%d",f);
	return 0;
}
