#include<bits/stdc++.h>
using namespace std;
typedef long long int64;
const int B = 1000000000;
const int L = 9;
inline int intcmp(int a, int b)
{
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else
        return 0;
}
struct BigInt
{
    vector<int> a;
    BigInt(){}
    BigInt(int n)
    {
        while (n > 0)
            a.push_back(n % B), n /= B;
    }
    BigInt(int64 n)
    {
        while (n > 0)
            a.push_back(n % B), n /= B;
    }
    inline void clr0()
    {
        while (!a.empty() && a.back() == 0)
            a.pop_back();
    }
    inline BigInt &operator+=(const BigInt &rhs)
    {
        a.resize(max(a.size(), rhs.a.size()));
        int t = 0;
        for (int i = 0; i < (int)rhs.a.size(); i++)
        {
            a[i] += rhs.a[i] + t;
            t = a[i] >= B;
            a[i] -= B & (-t);
        }
        for (int i = (int)rhs.a.size(); t != 0 && i < (int)a.size(); i++)
        {
            a[i] += t;
            t = a[i] >= B;
            a[i] -= B & (-t);
        }
        if (t != 0)
            a.push_back(t);
        return *this;
    }
    inline BigInt &operator-=(const BigInt &rhs)
    {
        a.resize(max(a.size(), rhs.a.size()));
        int t = 0;
        for (int i = 0; i < (int)rhs.a.size(); i++)
        {
            a[i] -= rhs.a[i] + t;
            t = a[i] < 0;
            a[i] += B & (-t);
        }
        for (int i = (int)rhs.a.size(); t != 0 && i < (int)a.size(); i++)
        {
            a[i] -= t;
            t = a[i] < 0;
            a[i] += B & (-t);
        }
        clr0();
        return *this;
    }
    inline BigInt &operator*=(const BigInt &rhs)
    {
        int na = (int)a.size();
        a.resize(na + rhs.a.size());
        for (int i = na - 1; i >= 0; i--)
        {
            int ai = a[i];
            int64 t = 0;
            a[i] = 0;
            for (int j = 0; j < (int)rhs.a.size(); j++)
            {
                t += a[i + j] + (int64)ai * rhs.a[j];
                a[i + j] = t % B;
                t /= B;
            }
            for (int j = (int)rhs.a.size(); t != 0 && i + j < (int)a.size(); j++)
            {
                t += a[i + j];
                a[i + j] = t % B;
                t /= B;
            }
            assert(t == 0);
        }
        clr0();
        return *this;
    }
    inline BigInt &operator/=(const BigInt &rhs)
    {
        return *this = div(rhs);
    }
    inline BigInt &operator%=(const BigInt &rhs)
    {
        return div(rhs), *this;
    }
    inline BigInt &shlb(int l = 1)
    {
        if (a.empty())
            return *this;
        a.resize(a.size() + l);
        for (int i = (int)a.size() - 1; i >= l; i--)
            a[i] = a[i - l];
        for (int i = 0; i < l; i++)
            a[i] = 0;
        return *this;
    }
    inline BigInt &shrb(int l = 1)
    {
        for (int i = 0; i < (int)a.size() - l; i++)
            a[i] = a[i + l];
        a.resize(max((int)a.size() - l, 0));
        return *this;
    }
    inline int cmp(const BigInt &rhs) const
    {
        if (a.size() != rhs.a.size())
            return intcmp(a.size(), rhs.a.size());
        for (int i = (int)a.size() - 1; i >= 0; i--)
            if (a[i] != rhs.a[i])
                return intcmp(a[i], rhs.a[i]);
        return 0;
    }
    inline BigInt div(const BigInt &rhs)
    {
        assert(!rhs.a.empty());
        if (rhs > *this)
            return 0;
        BigInt q, r;
        q.a.resize((int)a.size() - (int)rhs.a.size() + 1);
        for (int i = (int)a.size() - 1; i > (int)a.size() - (int)rhs.a.size(); i--)
        {
            r.shlb();
            r += a[i];
        }
        for (int i = (int)a.size() - (int)rhs.a.size(); i >= 0; i--)
        {
            r.shlb();
            r += a[i];
            if (r.cmp(rhs) < 0)
                q.a[i] = 0;
            else
            {
                int le = 0, ri = B;
                while (le != ri)
                {
                    int mi = (le + ri) / 2;
                    if ((rhs * mi).cmp(r) <= 0)
                        le = mi + 1;
                    else
                        ri = mi;
                }
                q.a[i] = le - 1;
                r -= rhs * q.a[i];
            }
        }
        q.clr0();
        *this = r;
        return q;
    }
    friend inline BigInt operator+(const BigInt &lhs, const BigInt &rhs)
    {
        BigInt res = lhs;
        return res += rhs;
    }
    friend inline BigInt operator-(const BigInt &lhs, const BigInt &rhs)
    {
        BigInt res = lhs;
        return res -= rhs;
    }
    friend inline BigInt operator*(const BigInt &lhs, const BigInt &rhs)
    {
        BigInt res = lhs;
        return res *= rhs;
    }
    friend inline BigInt operator/(const BigInt &lhs, const BigInt &rhs)
    {
        BigInt res = lhs;
        return res.div(rhs);
    }
    friend inline BigInt operator%(const BigInt &lhs, const BigInt &rhs)
    {
        BigInt res = lhs;
        return res.div(rhs), res;
    }
    friend inline ostream &operator<<(ostream &out, const BigInt &rhs)
    {
        if (rhs.a.size() == 0)
            out << "0";
        else
        {
            out << rhs.a.back();
            for (int i = (int)rhs.a.size() - 2; i >= 0; i--)
                out << setfill('0') << setw(L) << rhs.a[i];
        }
        return out;
    }
    friend inline bool operator<(const BigInt &lhs, const BigInt &rhs)
    {
        return lhs.cmp(rhs) < 0;
    }
    friend inline bool operator<=(const BigInt &lhs, const BigInt &rhs)
    {
        return lhs.cmp(rhs) <= 0;
    }
    friend inline bool operator>(const BigInt &lhs, const BigInt &rhs)
    {
        return lhs.cmp(rhs) > 0;
    }
    friend inline bool operator>=(const BigInt &lhs, const BigInt &rhs)
    {
        return lhs.cmp(rhs) >= 0;
    }
    friend inline bool operator==(const BigInt &lhs, const BigInt &rhs)
    {
        return lhs.cmp(rhs) == 0;
    }
    friend inline bool operator!=(const BigInt &lhs, const BigInt &rhs)
    {
        return lhs.cmp(rhs) != 0;
    }
};
BigInt f[20000];
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
f[1]=1;
f[2]=5;
f[3]=11;
f[4]=36;
f[5]=95;
f[6]=281;
f[7]=781;
f[8]=2245;
f[9]=6336;
f[10]=18061;
f[11]=51205;
f[12]=145601;
f[13]=413351;
f[14]=1174500;
f[15]=3335651;
f[16]=9475901;
f[17]=26915305;
f[18]=76455961;
f[19]=217172736;
f[20]=616891945;
f[21]=1752296281;
f[22]=4977472781;
f[23]=14138673395;
f[24]=40161441636;
long long n,m;
for(int i=25;i<=11000;i++)
{
	f[i]=f[i-1]+5*f[i-2]+f[i-3]-f[i-4];
}

	while(scanf("%d%d",&n,&m)==2&&n+m)
	{
		cout<<f[n]%m<<endl;
	}
}
