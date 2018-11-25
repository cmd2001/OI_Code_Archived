#include<cstdio>
#include<algorithm>
#include<cmath>
const double eps=1e-8;

double ax,ay,bx,by,cx,cy,dx,dy,p,q,r;

inline double dis(double x,double y,double xx,double yy) {
    const double dx = x - xx , dy = y - yy;
    return std::sqrt( dx * dx + dy * dy );
}
inline double tri_in(double x,double y) {
    double ll = 0 , rr = 1, lmid , rmid , lx , rx , ly , ry , cl , cr;
    while( fabs( ll - rr ) > eps ) {
        lmid = ( ll + ll + rr ) / 3 , rmid = ( ll + rr + rr ) / 3 ,
        lx = ( cx - dx ) * lmid + dx , ly = ( cy - dy ) * lmid + dy ,
        rx = ( cx - dx ) * rmid + dx , ry = ( cy - dy ) * rmid + dy ,
        cl = dis(ax,ay,x,y) / p + dis(x,y,lx,ly) / r + dis(lx,ly,dx,dy) / q ,
        cr = dis(ax,ay,x,y) / p + dis(x,y,rx,ry) / r + dis(rx,ry,dx,dy) / q ;
        if( cl > cr ) ll = lmid;
        else rr = rmid;
    }
    lmid = ( ll + ll + rr ) / 3 , rmid = ( ll + rr + rr ) / 3 ,
    lx = ( cx - dx ) * lmid + dx , ly = ( cy - dy ) * lmid + dy ,
    rx = ( cx - dx ) * rmid + dx , ry = ( cy - dy ) * rmid + dy ,
    cl = dis(ax,ay,x,y) / p + dis(x,y,lx,ly) / r + dis(lx,ly,dx,dy) / q ,
    cr = dis(ax,ay,x,y) / p + dis(x,y,rx,ry) / r + dis(rx,ry,dx,dy) / q ;
    return std::min( cl , cr );
}
inline double tri() {
    double ll = 0 , rr = 1 , lmid , rmid , lx , rx , ly , ry , cl , cr;
    while( fabs( ll - rr ) > eps ) {
        lmid = ( ll + ll + rr ) / 3 , rmid = ( ll + rr + rr ) / 3 ,
        lx = ( ax - bx ) * lmid + bx , ly = ( ay - by ) * lmid + by ,
        rx = ( ax - bx ) * rmid + bx , ry = ( ay - by ) * rmid + by ,
        cl = tri_in(lx,ly) , cr = tri_in(rx,ry);
        if( cl > cr ) ll = lmid;
        else rr = rmid;
    }
    lmid = ( ll + ll + rr ) / 3 , rmid = ( ll + rr + rr ) / 3 ,
    lx = ( ax - bx ) * lmid + bx , ly = ( ay - by ) * lmid + by ,
    rx = ( ax - bx ) * rmid + bx , ry = ( ay - by ) * rmid + by ,
    cl = tri_in(lx,ly) , cr = tri_in(rx,ry);
    return std::min( cl , cr );
}

int main() {
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&ax,&ay,&bx,&by,&cx,&cy,&dx,&dy,&p,&q,&r);
    printf("%0.2lf\n",tri());
    return 0;
}

