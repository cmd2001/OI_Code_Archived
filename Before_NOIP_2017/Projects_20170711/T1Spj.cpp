#include<bits/stdc++.h>
using namespace std;

ofstream fscore,freport;
ifstream fin,fout,fstd;

int main(int argc,char *argv[])
{
    fin.open(argv[1]);
    fout.open(argv[2]);
    fstd.open(argv[3]);
    fscore.open(argv[5]);
    freport.open(argv[6]);

    static long long int n,sum,ans=0;
    fin>>n>>sum;
    for(int i=1,t;i<=n;i++)
    {
        fout>>t;
        ans+=t;
    }

    fscore<<10*(ans==sum)<<endl;


    fin.close();
    fout.close();
    fstd.close();
    fscore.close();
    freport.close();
    return 0;
}
