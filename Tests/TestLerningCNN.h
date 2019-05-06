#pragma once
#include "Test.h"
#include "CNNLearns.h"

class TestLerningCNN : public TestSuite::Test
{
public:
	TestLerningCNN() : A() {}
	void run() {
		testConstruktors();
		testMetods();
		testExeptions();

	}
	void testConstruktors();
	void testMetods();
	void testExeptions();


	~TestLerningCNN();
private:
	D_CNNLeaning A;
};