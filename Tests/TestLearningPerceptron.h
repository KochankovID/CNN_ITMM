#pragma once
#include "Test.h"
#include "PLearns.h"

class TestLearningPerceptron : public TestSuite::Test
{
public:
	TestLearningPerceptron() : A(){}
	void run() {
		testConstruktors();
		testMetods();
		testExeptions();

	}
	void testConstruktors();
	void testMetods();
	void testExeptions();


	~TestLearningPerceptron();
private:
	DD_Leaning A;
};