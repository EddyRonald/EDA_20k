#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>

using namespace std;
typedef long long ll;

int main() {

	ll x = 10000;
	ll b = 15000;
	ll c = 20000;
	ll d = 25000;
	ll s1 = 4;

	vector<ll> Tams;
	Tams.push_back(x); Tams.push_back(b); Tams.push_back(c); Tams.push_back(d);
	vector<ll> Dim;
	Dim.push_back(s1);
	for(short i = s1;i <= 20;i +=2)
		Dim.push_back(i);

	vector<vector<ll> > A;
	for (short ii = 0; ii < Dim.size(); ii++) {
		for (short jj = 0; jj < Tams.size(); jj++) {
			srand(time(NULL));
			for (short i = 0; i < Tams[jj]; i++) {
				vector<ll> a;
				for (short j = 0; j < Dim[ii]; j++) {
					ll r = rand() % d;
					a.push_back(r);
				}
				A.push_back(a);
				a.clear();
			}
			auto begin = chrono::high_resolution_clock::now();
			for (short i = 0; i < A.size(); i++) {
				for (short j = i + 1; j < A.size(); j++) {
					float val = 0;
					for (short k = 0; k < A[i].size(); k++) {
						val += pow(A[j][k] - A[i][k], 2);
					}
					float distance = sqrt(val);
				}
			}
			auto done = chrono::high_resolution_clock::now();
			auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(done - begin);
			cout << "\nSize of group " << Tams[jj] << " with dimension " << Dim[ii] << " and time " << elapsed.count() << " ms ";
			A.clear();

		}
	}
	return 0;
}
