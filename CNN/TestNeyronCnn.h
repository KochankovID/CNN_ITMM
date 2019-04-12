#pragma once
#include <Test.h>
#include "NeyronCnn.h"

class TestNeyronCnn : public TestSuite::Test
{
public:
	TestNeyronCnn() : A(3, 3), B(6, 6) {}
	void run() {
		testMetods();
		testOperators();
		testExeptions();
		Visualisator();
	}
	void testMetods();
	void testOperators();
	void testExeptions();
	void Visualisator();

	~TestNeyronCnn();
private:
	Neyron—nn A, B;
};

