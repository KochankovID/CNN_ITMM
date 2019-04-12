#include "TestNeyronCnn.h"
#include <fstream>

using namespace std;
void TestNeyronCnn::testMetods()
{
	double **f = new double*[1];
	f[0] = new double[1];
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

	NeyronСnn FF(4, 4);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			FF[i][j] = std::_Max_value(i, j);
		}
	}
	FF.Pooling(2, 2);
	test_(FF.getN() == 2);
	test_(FF.getM() == 2);

	test_((FF[0][0] == 1) || (FF[0][1] == 3) || (FF[1][0] == 3) || (FF[1][1] == 3));

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

void TestNeyronCnn::Visualisator()
{
	ofstream file;
	file.open("NeyronTest.txt");

	NeyronСnn M(6, 6);
	int o = 0;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			M[i][j] = o++;
		}
	}
	M.Padding();
	file << M;
	file << endl;
	Filter a(2, 2);
	a[0][0] = 1;
	a[0][1] = 1;
	a[1][0] = 1;
	a[1][1] = 1;
	M.Svertka(a);
	file << M;
	file << endl;
	M.Pooling(2, 2);
	file << M;
	file << endl;
	file.close();
	
}

TestNeyronCnn::~TestNeyronCnn()
{
}
