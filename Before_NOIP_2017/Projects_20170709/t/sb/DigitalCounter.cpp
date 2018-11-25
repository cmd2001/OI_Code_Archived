#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

long long h[15];
int b[20];
const int c[]={6,2,5,5,4,5,6,3,7,5};

int main()
{
	freopen("DigitalCounter.in","r",stdin);
	freopen("DigitalCounter.out","w",stdout);

	int n;
	long long x;
	cin>>n>>x;

	for(int z=0;x;z++) {
		b[z]=x%10;
		x/=10;
	}

	for(int j=b[0]+1;j<10;j++) {
		if(c[j]==c[b[0]]) {
			cout<<j-b[0]<<endl;
			return 0;
		}
		h[c[j]-c[b[0]]+5]=j-b[0];
	}

	for(int i=1;i<n;i++) {
		for(int j=b[i]+1;j<10;j++) {
			int d=c[j]-c[b[i]];
			if(h[-d+5]) {
				cout<<(long long)pow(10,i)*(j-b[i])+h[-d+5]<<endl;
				return 0;
			}
			for(int k=0;k<=10;k++) {
				if(d+k&&d+k<=10&&!h[d+k]&&h[k]) {
					h[d+k]=(long long)pow(10,i)*(j-b[i])+h[k];
				}
			}
		}
	}

	cout<<(long long)pow(10,n)<<endl; //fuck you

	fclose(stdin);
	fclose(stdout);
	return 0;
}