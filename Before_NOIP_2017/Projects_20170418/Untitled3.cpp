#include <cstdio>
#include <cstdlib>
#include<iostream>
#define debug cout
#define z 2005
#define q(e) scanf("%d",&e);
#define r(e,x,y) for(e=x;i<=y;i++)
#define A(e) printf("%c ",e);
using namespace std;
int a[z],b[z],f[z],u=1,v,d=2,p=1,i,j,k=2,n;
char c[z];
bool o(){
	if(!v) return 1;
	r(i,k+1,n) if(f[i]>f[k]&&f[i]>b[v]) break;
	debug<<"i="<<i<<endl;
	r(j,i+1,n) if(f[j]<f[k]) return 0;
	return 1;
}
void s(int t){
	if(t>2*n){
		r(i,1,2*n) A(c[i])
		exit(0);
	}
	if(a[u]==p&&u) p++,u--,c[d++]='b',s(t+1);
	if(b[v]==p&&v) p++,v--,c[d++]='d',s(t+1);
	if(a[u]>f[k]&&o()||!u) {debug<<f[k]<<"into a"<<endl;c[d++]='a',a[++u]=f[k++],s(t+1);}
	if(b[v]>f[k]||!v) {debug<<f[k]<<"into b"<<endl;c[d++]='c',b[++v]=f[k++],s(t+1);}
}
int main(){
	q(n)
	r(i,1,n) q(f[i])
	a[1]=f[1],c[1]='a';
	s(2);
	A('0')
}
