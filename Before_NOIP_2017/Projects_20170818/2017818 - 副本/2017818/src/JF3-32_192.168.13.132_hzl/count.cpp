#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int mod;
struct Matrix{
	int n, m;
	long long num[5][5];
	Matrix(int _n, int _m){
		n = _n;
		m = _m;
		memset(num, 0, sizeof num);
	}
	Matrix operator * (const Matrix &a){
		Matrix b(n, a.m);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= a.m; j++)
				for(int k = 1; k <= m; k++)
					b.num[i][j] = (b.num[i][j] + num[i][k] * a.num[k][j]) % mod;
		return b;
	}
};
Matrix ksm(Matrix a, int b){
	Matrix s(4, 4);
	for(int i = 1; i <= 4; i++)
		s.num[i][i] = 1;
	while(b){
		if(b & 1) s = s * a;
		a = a * a;
		b >>= 1;
	}
	return s;
}
int main(){
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	int n;
	cin >> n >> mod;
	Matrix cs(1, 4), zy(4, 4);
	cs.num[1][1] = 1;
	cs.num[1][2] = 5 % mod;
	cs.num[1][3] = 11 % mod;
	cs.num[1][4] = 36 % mod;
	zy.num[2][1] = zy.num[3][2] = zy.num[4][3] = zy.num[2][4] = zy.num[4][4] = 1;
	zy.num[3][4] = 5 % mod;
	zy.num[1][4] = -1 + mod;
	cs = cs * ksm(zy, n - 1);
	cout << cs.num[1][1] << endl;
	return 0;
}
// 1 5 11 36 95 281 781 

// 1 5 1 -1

// f[1] f[2] f[3] f[4]   *  0 0 0 -1
//							1 0 0 1
//							0 1 0 5
//							0 0 1 1

