#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
const double pi = std::acos(-1.0);
const int maxn=65537;

struct Complex {
    double r,i;
    friend Complex operator + (const Complex &a,const Complex &b) { return (Complex){a.r+b.r,a.i+b.i}; }
    friend Complex operator - (const Complex &a,const Complex &b) { return (Complex){a.r-b.r,a.i-b.i}; }
    friend Complex operator * (const Complex &a,const Complex &b) { return (Complex){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r}; }
}da[maxn],db[maxn];

inline void FFT(Complex* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        const Complex per = (Complex){std::cos(pi*tpe/h),std::sin(pi*tpe/h)};
        for(int st=0;st<n;st+=len) {
            Complex w = (Complex){1.0,0.0};
            for(int pos=0;pos<h;pos++) {
                const Complex u = dst[st+pos] , v = dst[st+pos+h] * w;
                dst[st+pos] = u + v , dst[st+pos+h] = u - v , w = w * per;
            }
        }
    }
    if( !~tpe ) for(int i=0;i<n;i++) dst[i].r /= n;
}

inline void mul(int* dst,const int* sa,const int* sb,int &len,const int &la,const int &lb) {
    for(len=1;len<=la+lb;len<<=1) ;
    memset(da,0,sizeof(Complex)*len) , memset(db,0,sizeof(Complex)*len);
    for(int i=0;i<len;i++) da[i] = (Complex){(double)sa[i],0} , db[i] = (Complex){(double)sb[i],0};
    FFT(da,len,1) , FFT(db,len,1);
    for(int i=0;i<len;i++) da[i] = da[i] * db[i];
    FFT(da,len,-1);
    for(int i=0;i<len;i++) dst[i] = (int)( da[i].r + 0.5 );
    for(int i=0;i<len;i++) dst[i+1] += dst[i] / 10 , dst[i] %= 10;
    while( len && !dst[len-1] ) --len;
}

struct BigInt {
    int dat[maxn],len;
    BigInt() { memset(dat,0,sizeof(dat)) , len = 0; }
    BigInt operator = (int r) {
        while(r) dat[len++] = r % 10 , r /= 10;
        return *this;
    }
    friend BigInt operator + (const BigInt &a,const BigInt &b) {
        BigInt ret; ret.len = std::max( a.len , b.len + 2 );
        for(int i=0;i<ret.len;i++) {
            ret.dat[i] += a.dat[i] + b.dat[i] ,
            ret.dat[i+1] += ret.dat[i] / 10 , ret.dat[i] %= 10;
        }
        while( ret.len && !ret.dat[ret.len-1] ) --ret.len;
        return ret;
    }
    friend BigInt operator * (const BigInt &a,const BigInt &b) {
        BigInt ret;
        mul(ret.dat,a.dat,b.dat,ret.len,a.len,b.len);
        return ret;
    }
    inline void print(char lst=0) const {
        for(int i=len-1;~i;i--) putchar(dat[i]+'0');
        if(lst) putchar(lst);
    }
}two,ans;

struct Matrix {
    BigInt dat[2][2];
    Matrix(int tpe=0) {
        if(tpe) for(int i=0;i<2;i++) dat[i][i] = 1;
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    ret.dat[i][j] = ret.dat[i][j] + a.dat[i][k] * b.dat[k][j];
        return ret;
    }
    inline void print() const {
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) dat[i][j].print(j?'\n':' ');
    }
}ini,trans;

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}

int main() {
    static int t,n;
    ini.dat[0][0] = ini.dat[0][1] = 1 , trans.dat[0][0] = 4 , trans.dat[1][0] = trans.dat[1][1] = 1 , two = 2;
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&n) , ans = (ini*fastpow(trans,(n-1)>>1)).dat[0][0];
        if( ! ( n & 1 ) ) ans = ans * two;
        ans.print('\n');
    }
    return 0;
}

