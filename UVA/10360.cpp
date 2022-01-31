#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int MAX_SIZE = 1025;
int MAP[MAX_SIZE][MAX_SIZE];
int psum[MAX_SIZE][MAX_SIZE];

void init();
void process();

void build_psum();
int query(int lx, int ly, int rx, int ry);

int main(int argc, char* argv[]) {
	int T;
	cin >> T;
	while (T--) {
		init();
		process();
	}
	return 0;
}

void init() {
	for (int i = 0; i < MAX_SIZE; i++) {
		fill(MAP[i], MAP[i] + MAX_SIZE, 0);
		fill(psum[i], psum[i] + MAX_SIZE, 0);
	}
}

void process() {

	int d, N;
	cin >> d;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int rx, ry, rn;
		cin >> rx >> ry >> rn;
		MAP[rx][ry] = rn;
	}

	// build 2D prefix sum
	build_psum();

	// query all square area with length d
	int x = 0, y = 0, n = 0;
	for (int i = d; i < MAX_SIZE-d; i++) {
		for (int j = d; j < MAX_SIZE-d; j++) {
			int k = query(i - d, j - d, i + d, j + d);
			if (k > n) {
				x = i, y = j, n = k;
			}
		}
	}
	cout << x << ' ' << y << ' ' << n << endl;
}



void build_psum() {

	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (i == 0 || j == 0 ) {
				psum[i][j] = MAP[i][j];
			}
			else {
				psum[i][j] = psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + MAP[i][j];
			}
		}
	}

}
int query(int lx, int ly, int rx, int ry) {
	int A = (lx > 0 && ly > 0) ? psum[lx - 1][ly - 1] : 0;
	int B = (lx > 0) ? psum[lx - 1][ry] : 0;
	int C = (ly > 0) ? psum[rx][ly - 1] : 0;
	int D = psum[rx][ry];
	return D - B - C + A;
}