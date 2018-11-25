#include <iostream>
#include <fstream>
using std::endl;
std::ifstream fin("egg.in");
std::ofstream fout("egg.out");
int n,m;
unsigned long long lr,f[1001][1001];//²ãÊý ¸öÊý 
int main() {
	fin>>n>>m;
	for (int i=1;i<=n;++i)
		f[i][1]=i;
	for (int i=1;i<=n;++i)
		for (int j=2;j<=m;++j) {
			f[i][j]=1+f[i-1][j];
			for (int k=2;k<=i;++k)
				if ((lr=1+std::max(f[i-k][j],f[k-1][j-1]))<f[i][j])
					f[i][j]=lr;
		}
	fout<<f[n][m]<<endl;
	fin.close();
	fout.close();
}

