#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;

int in[maxn],n,m;
vector<int> ats,nums;

inline int calc() {
    int ret = 0;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            ret += ( in[j] < in[i] );
    return ret;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    printf("%d\n",calc());
    for(int i=1;i<=m;i++) {
        //cout<<"i = "<<i<<endl;
        int p;scanf("%d",&p);
        ats.clear() , nums.clear();
        ats.push_back(p) , nums.push_back(in[p]);
        for(int j=p;j<=n;j++)
            if( in[j] < in[p] )
                ats.push_back(j) , nums.push_back(in[j]);
        sort(nums.begin(),nums.end());
        for(unsigned j=0;j<nums.size();j++)
            in[ats[j]] = nums[j];
        printf("%d\n",calc());
    }
    return 0;
}