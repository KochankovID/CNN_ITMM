#include "TestFilter.h"
#include <fstream>

using namespace std;

void TestFilter::testMetods()
{
	ofstream out("FilterTest.txt");
	out << A;
	Filter<int> Y;
	Y = A.roate_180();
	test_(Y.getN() == A.getN());
	test_(Y.getM() == A.getM());
	int n = A.getN()-1, m = A.getM()-1;
	for (int i = n; i >= 0; i--) {
		for (int j = m; j >= 0; j--) {
			test_(Y[i][j] == A[n - i][m - j]);
		}
	}
	out << Y;
	out.close();
}

TestFilter::~TestFilter()
{
}
