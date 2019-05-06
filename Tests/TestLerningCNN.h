#pragma once
#include "Test.h"
#include "PLearns.h"

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
	DD_Leaning A;
};