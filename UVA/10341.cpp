#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

double f(double x, double p, double q, double r, double s, double t, double u){
	return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x*x + u;
}

int main(void){
	double eps = 1e-9;
	double p, q, r, s, t, u;
	while( cin >> p >> q >> r >> s >> t >> u ){
		double lb = 0.0, rb = 1.0;
		
		while( rb - lb > eps ){
			double mid = ( rb + lb ) / 2.0;
			double val = f(mid, p, q, r, s, t, u );
			if( val > 0 ){
				lb = mid;
			}
			else{
				rb = mid;
			}
		}
		
		double x = (lb + rb) / 2.0;
		double val = f(x, p, q, r, s, t, u );
		//printf("x = %.4lf, f(x) = %.16lf\n", x, val );
		if( abs(val) < 1e-6 )
			printf("%.4lf\n", x );
		else
			printf("No solution\n");
	}
	return 0;
}