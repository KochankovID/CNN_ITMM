#pragma once
#include "Test.h"
#include "Perceptrons.h"

class TestPeceptron : public TestSuite::Test
{
public:
	TestPeceptron() : A(), B() {}
	void run() {
		testMetods();
		testExeptions();

	}
	void testMetods();
	void testExeptions();


	~TestPeceptron();
private:
	ID_Perceptron A;
	DD_Perceptron B;
};