#include <bits/stdc++.h>

using namespace std;
#define PI (3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253)

long double a, b, x, y, r, deg, L;
long double theta;

int main(void){
    cin >> a >> b >> x >> y >> r >> deg >> L;
    theta = deg / 180 * PI;
    // [r, a-r] -> [0, a-r-r], [r, b-r] -> [0, b-r-r]
    long double X = L * cos(theta) + x - r;
    long double Y = L * sin(theta) + y - r;
    
    cout << X << ' ' << Y << endl;
    long double ax, ay;
    ax = (X < 0) ? -X : X;
    ay = (Y < 0) ? -Y : Y;
    int mx = floorl( ax / (a - r - r) ), my = floorl( ay / (b - r - r) );

    cout << mx << ' ' << my << endl;
    // [0, a-r-r] -> [r, a-r] ...
    if( mx % 2 ) ax = a - r - fmodl(ax, a - r - r);
    else         ax = r + fmodl(ax, a - r - r);
    if( my % 2 ) ay = b - r - fmodl(ay, b - r - r);
    else         ay = r + fmodl(ay, b - r - r);

    printf("%.8LF %.8LF", ax, ay);
    return 0;
}