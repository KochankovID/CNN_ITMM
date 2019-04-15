#include <fstream>
#include <iostream>
#include <string>
#include "TestMatrix.h"
#include "TestNeyronCnn.h"
#include <Suite.h>

using namespace std;
int main()
{
	TestSuite::Suite t("CNN TEST");
	t.addTest(new TestMatrix());
	t.addTest(new TestNeyronCnn());
	t.run();
	t.report();
	t.free();
	system("pause");
}
