#pragma once
#include "Test.h"
#include "Filter.h"

class TestFilter : public TestSuite::Test
{
public:
	TestFilter() : A(3, 3) {
		int t = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				A[i][j] = t++;
			}
		}
	}
	void run() {
		testMetods();
	}
	void testMetods();

	~TestFilter();
private:
	Filter<int> A;
};
