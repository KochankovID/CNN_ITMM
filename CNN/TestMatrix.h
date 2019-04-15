#pragma once
#include <Test.h>
#include "Matrix.h"

class TestMatrix : public TestSuite::Test
{
public:
	TestMatrix() : A(3, 3), B(3, 3) {
		int t = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				A[i][j] = t;
				B[i][j] = t++;
			}
		}
	}
	void run() {
		testConstruktors();
		testMetods();
		testOperators();
		testExeptions();
	}
	void testConstruktors();
	void testMetods();
	void testOperators();
	void testExeptions();

	~TestMatrix();
private:
	Matrix<int> A;
	Matrix<double> B;
};

