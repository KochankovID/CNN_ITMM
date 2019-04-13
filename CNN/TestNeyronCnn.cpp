#include "TestNeyronCnn.h"
#include <fstream>

using namespace std;
void TestNeyronCnn::testMetods()
{
	double **f = new double*[1];
	f[0] = new double[1];
	f[0][0] = 5;

	Matrix FF(f,1, 1);
	NeyronСnn F(1);
	F.Padding(FF);
	test_(FF.getN() == 3);
	test_(FF.getM() == 3);
	test_(((FF[0][0] == 0) || (FF[0][1] == 0) || (FF[0][2] == 0) || (FF[1][0] == 0) || (FF[1][2] == 0) || (FF[2][0] == 0) || (FF[2][1] == 0) || (FF[2][2] == 0) || (FF[1][1] != 0)));

	Filter y(2, 2);
	F.Svertka(y,FF);

	test_(FF.getN() == 2);
	test_(FF.getM() == 2);
	test_(FF[0][0] == 0);
	test_(FF[0][1] == 0);
	test_(FF[1][0] == 0);
	test_(FF[1][1] == 0);

	Matrix T(1, 1);

	F.Padding(T);
	F.SetStep(2);
	test_(F.GetStep() == 2);

	F.Svertka(y,T);

	test_(T.getN() == 1);
	test_(T.getM() == 1);
	test_(T[0][0] == 0);

	Matrix FFF(4, 4);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			FFF[i][j] = std::_Max_value(i, j);
		}
	}
	F.Pooling(FFF, 2,2);
	test_(FFF.getN() == 2);
	test_(FFF.getM() == 2);

	test_((FFF[0][0] == 1) || (FFF[0][1] == 3) || (FFF[1][0] == 3) || (FFF[1][1] == 3));

}

void TestNeyronCnn::testExeptions()
{
	try {
		A.SetStep(-4);
		fail_("Не вызванно исключение  метода установки шага");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	A.SetStep(5);
	Matrix o(2, 2);
	Filter y(2, 2);

	try {
		A.Svertka(y, o);
		fail_("Не вызванно исключение  метода установки шага");
	}catch (std::runtime_error& e) {
		succeed_();
	}
}

void TestNeyronCnn::Visualisator()
{
	ofstream file;
	file.open("NeyronTest.txt");

	Matrix M(6, 6);
	int o = 0;
	A.SetStep(1);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			M[i][j] = o++;
		}
	}
	A.Padding(M);
	file << M;
	file << endl;

	Filter a(2, 2);
	a[0][0] = 1;
	a[0][1] = 1;
	a[1][0] = 1;
	a[1][1] = 1;

	A.Svertka(a, M);
	file << M;
	file << endl;
	A.Pooling(M, 2, 2);
	file << M;
	file << endl;
	file.close();
	
}

TestNeyronCnn::~TestNeyronCnn()
{
}
