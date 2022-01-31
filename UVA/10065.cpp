#include <bits/stdc++.h>

using namespace std;

struct Point2d{
    double x, y;
    Point2d() : x(0), y(0) {};
    Point2d(double _x, double _y) : x(_x), y(_y) {};
    Point2d(const Point2d& p) : x(p.x), y(p.y) {};

    double cross(const Point2d& other){
        return this->x * other.y - this->y * other.x;
    }
    double length2(){
        return this->x * this->x + this->y * this->y;
    }

    Point2d operator- (const Point2d& other) const{
        return Point2d(this->x - other.x, this->y - other.y);
    }
};

bool process(int cnt);

vector<Point2d> convex_hull( const vector<Point2d>& point );

int main(void){
    int cnt = 1;
    while(process(cnt++));
    return 0;
}

bool process(int cnt){
    int N;
    cin >> N;
    if( N == 0 ) return false;

    vector<Point2d> points;
    for(int i=0; i<N; i++){
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    double org_area_2 = 0.0;
    for(int i=0; i<points.size(); i++){
        // std::cout << points[i].cross(points[(i+1)%points.size()]) / 2 << endl;
        org_area_2 += points[i].cross(points[(i+1)%points.size()]);
    }
    org_area_2 = abs(org_area_2);

    double CH_area_2 = 0.0;
    vector<Point2d> CH = convex_hull(points);
    // std::cout << "convex hull" << std::endl;
    for(int i=0; i<CH.size(); i++){
        // std::cout << CH[i].x << ' ' << CH[i].y << std::endl;
        CH_area_2 += CH[i].cross(CH[(i+1)%CH.size()]);
    }
    CH_area_2 = abs(CH_area_2);

    double ans = 1.0 - org_area_2 / CH_area_2;

    cout << "Tile #" << cnt << endl;
    cout << fixed << setprecision(2);
    cout << "Wasted Space = " << 100 * ans << " %" << endl;
    cout << endl;
    return true;
}

bool pos_cmp(const Point2d& a, const Point2d& b){
    return ( a.y < b.y ) || ( a.y == b.y && a.x < b.x );
}

struct MyCmp{
    Point2d orig;
    bool operator() (const Point2d& a, const Point2d& b){
        Point2d OA = a - orig;
        Point2d OB = b - orig;
        double c = OA.cross(OB);
        return c > 0 || ( c == 0 && OA.length2() < OB.length2() );
    };
};

vector<Point2d> convex_hull( const vector<Point2d>& points ){
    vector<Point2d> P;
    for(const Point2d& p : points){
        P.emplace_back(p);
    }
    
    swap(P.front(), *min_element(P.begin(), P.end(), pos_cmp) );
    P.emplace_back(P.front());

    MyCmp angle_cmp;
    angle_cmp.orig = P[0];
    sort(P.begin()+1, P.end(), angle_cmp);

    vector<Point2d> CH;

    for(int i=0; i<P.size(); i++){
        int sz = CH.size();
        while( sz >= 2 && (CH[sz-1] - CH[sz-2]).cross(P[i] - CH[sz-2]) <= 0  ){
            CH.pop_back();
            sz--;
        }
        CH.emplace_back(P[i]);
    }
    // CH.pop_back();
    return CH;
}

/*
5 
0 0
2 0
2 2
1 1
0 2
5
0 0
0 2
1 3
2 2
2 0
0
*/