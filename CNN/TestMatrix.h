#pragma once
#include <Test.h>
#include "Matrix.h"

class TestMatrix : public TestSuite::Test
{
public:
	TestMatrix() : A(3, 3), B(3, 3) {}
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
	Matrix A, B;
};

