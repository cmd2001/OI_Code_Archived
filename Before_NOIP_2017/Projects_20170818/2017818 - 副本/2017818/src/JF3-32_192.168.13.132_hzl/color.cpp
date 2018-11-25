#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1ll << 31;
ll ksm(ll a, int b){
	ll s = 1;
	while(b){
		if(b & 1) s = s * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return s;
}
int main(){
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	int n, Max;
	cin >> n;
	Max = (1 << n) - 1;
	long long ans = 0;
	for(int count, i = 1; i <= Max; i++){
		count = 0;
		for(int t = 1; t <= i; t <<= 1)
			if(i & t) count++;
		ans = (ans + ksm(233, i) * count) % mod;
	}
	cout << ans << endl;
	return 0;
}
