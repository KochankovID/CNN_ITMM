#pragma once
#include "Test.h"
#include "NeyronCnn.h"

class TestNeyronCnn : public TestSuite::Test
{
public:
	TestNeyronCnn() : A(), B() {}
	void run() {
		testMetods();
		testExeptions();
		Visualisator();
	}
	void testMetods();
	void testExeptions();
	void Visualisator();

	~TestNeyronCnn();
private:
	Neyron�nn<int> A;
	Neyron�nn<double> B;
};

