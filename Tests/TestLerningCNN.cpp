#include "TestLerningCNN.h"
#include <fstream>

using namespace std;
void TestLerningCNN::testConstruktors()
{
	test_(A.getE() == 1);
	test_(A.getStep() == 1);
}

void TestLerningCNN::testMetods()
{
	// Тест установки коэфицента скорости обучения
	A.getE() = 2;
	test_(A.getE() == 2);
	A.getE() = 1;

	// Тест установки шага свертки
	A.getStep() = 5;
	test_(A.getStep() == 5);
	A.getStep() = 1;

	// Тест обратного распространения ошибки
	Matrix<double> X(3,3);
	for (int i = 0; i < 3; i++) {
		X[i][0] = 1;
		X[i][1] = 2;
		X[i][2] = 3;
	}
	Filter <double> F (2, 2);
	F.Fill(1);
	NeyronСnn<double> g;
	auto Out = g.Svertka(F, X);
	auto Dnext = A.ReversConvolution(Out, F);
	ofstream out("CNNLearningTest.txt");
	out << Dnext;
	test_(Dnext[0][0] == 6);
	test_(Dnext[0][1] == 16);
	test_(Dnext[0][2] == 10);
	test_(Dnext[1][0] == 12);
	test_(Dnext[1][1] == 32);
	test_(Dnext[1][2] == 20);
	test_(Dnext[2][0] == 6);
	test_(Dnext[2][1] == 16);
	test_(Dnext[2][2] == 10);

	Matrix<double> U(1, 1);
	U.Fill(6);
	A.getStep() = 2;
	auto Dnexts = A.ReversConvolution(U, F);
	out << Dnext;
	test_(Dnexts[0][0] == 6);
	test_(Dnexts[0][1] == 6);
	test_(Dnexts[0][2] == 0);
	test_(Dnexts[1][0] == 6);
	test_(Dnexts[1][1] == 6);
	test_(Dnexts[1][2] == 0);
	test_(Dnexts[2][0] == 0);
	test_(Dnexts[2][1] == 0);
	test_(Dnexts[2][2] == 0);

	// Тест применения градиента на фильтр
	A.GradDes(X, Out, F);
	test_(F[0][0] == 53);
	test_(F[0][1] == 85);
	test_(F[1][0] == 53);
	test_(F[1][1] == 85);
	out << F;

	// Тест распространение ошибки на подвыборочном слое
	Matrix<double> ppp(2, 2);
	ppp[0][0] = 1;
	ppp[0][1] = 2;
	ppp[1][0] = 3;
	ppp[1][1] = 4;

	auto UUU = A.ReversPooling(ppp, 2, 2);

	test_(UUU[0][0] == 1);
	test_(UUU[0][1] == 1);
	test_(UUU[0][2] == 2);
	test_(UUU[0][3] == 2);
	test_(UUU[1][0] == 1);
	test_(UUU[1][1] == 1);
	test_(UUU[1][2] == 2);
	test_(UUU[1][3] == 2);
	test_(UUU[2][0] == 3);
	test_(UUU[2][1] == 3);
	test_(UUU[2][2] == 4);
	test_(UUU[2][3] == 4);
	test_(UUU[3][0] == 3);
	test_(UUU[3][1] == 3);
	test_(UUU[3][2] == 4);
	test_(UUU[3][3] == 4);

	out << UUU;

	out.close();
}

void TestLerningCNN::testExeptions()
{
	try {
		A.getStep() = -4;
		Matrix<double> u(2, 2);
		Filter<double> uu(2, 2);
		A.ReversConvolution(u, uu);
		fail_("Не вызванно исключение свертки с неверным шагом!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}
	try {
		Matrix<double> u(10, 10);
		Matrix<double> uu(2, 2);
		Filter<double> uuu(2, 2);
		A.GradDes(u, uu,uuu);
		fail_("Не вызванно исключение свертки с неверным шагом!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}
}

TestLerningCNN::~TestLerningCNN()
{
}
