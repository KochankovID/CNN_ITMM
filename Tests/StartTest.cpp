#include <fstream>
#include <iostream>
#include <string>
#include "TestMatrix.h"
#include "TestNeyronCnn.h"
#include "TestPeceptron.h"
#include "TestLearningPerceptron.h"
#include "Suite.h"


using namespace std;
int main()
{
	TestSuite::Suite t("CNN TEST");
	t.addTest(new TestMatrix());
	t.addTest(new TestNeyronCnn());
	t.addTest(new TestPeceptron());
	t.addTest(new TestLearningPerceptron());
	t.run();
	t.report();
	t.free();
	system("pause");
	return 0;
}
