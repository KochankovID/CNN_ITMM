#include "TestNeyronCnn.h"
#include <fstream>

using namespace std;
void TestNeyronCnn::testMetods()
{
	int **f = new int*[1];
	f[0] = new int[1];
	f[0][0] = 5;

	NeyronСnn F(f,1, 1, 1);
	F.Padding();
	test_(F.getN() == 3);
	test_(F.getM() == 3);
	test_(((F[0][0] == 0) || (F[0][1] == 0) || (F[0][2] == 0) || (F[1][0] == 0) || (F[1][2] == 0) || (F[2][0] == 0) || (F[2][1] == 0) || (F[2][2] == 0) || (F[1][1] != 0)));

	Filter y(2, 2);
	F.Svertka(y);

	test_(F.getN() == 2);
	test_(F.getM() == 2);
	test_(F[0][0] == 0);
	test_(F[0][1] == 0);
	test_(F[1][0] == 0);
	test_(F[1][1] == 0);
	NeyronСnn T (f, 1, 1, 1);
	F = T;
	F.Padding();
	F.SetStep(2);
	test_(F.GetStep() == 2);
	F.Svertka(y);
	test_(F.getN() == 1);
	test_(F.getM() == 1);
	test_(F[0][0] == 0);
}

void TestNeyronCnn::testOperators()
{
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;

	B = A;
	test_(B.getN() == 3);
	test_(B.getM() == 3);
	test_(B[0][0] == 1);
	test_(B[0][1] == 2);
	test_(B[1][0] == 3);
	test_(B[1][1] == 4);

	ofstream file;
	file.open("NeyronText.txt");
	file << A;
	file.close();
	ifstream file1;
	file1.open("NeyronText.txt");
	file1 >> B;
	file1.close();
}

void TestNeyronCnn::testExeptions()
{
	try {
		A.SetStep(40);
		fail_("Не вызванно исключение  метода установки шага");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

}

TestNeyronCnn::~TestNeyronCnn()
{
}
