#include <fstream>
#include <iostream>
#include <string>
#include "Matrix.h"
#include "TestMatrix.h"

using namespace std;
int main()
{
	TestMatrix t;
	t.run();
	t.report();
	system("pause");
}
