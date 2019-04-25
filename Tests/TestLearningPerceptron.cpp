#include "Functors.h"
#include "TestLearningPerceptron.h"
#include "Weights.h"

class Sigm : public DD_Func
{
public:
	Sigm(const double& a_) : DD_Func(), a(a_) {};
	double a;
	double operator()(const double& x) {
		double f = 1;
		const double e = 2.7182818284;
		for (int i = 0; i < a*x; i++)
		{
			f *= 1 / e;
		}
		f++;
		return 1 / f;
	}
	~Sigm() {};
};

class SigmD : public Sigm
{
public:
	SigmD(const double& a_) : Sigm(a_) {};
	double operator()(const double& x) {
		double f = 1;
		f = Sigm::operator()(x)*(1 - Sigm::operator()(x));
		return f;
	}
	~SigmD() {};
};

void TestLearningPerceptron::testConstruktors()
{
	// Тест конструктор по умолчанию
	PerceptronLearning<double, double> B;
	test_(B.getE() == 1);

	// Тест конструктора инициализатора
	PerceptronLearning<int, int> O(0.4);
	test_(O.getE() == 0.4);
}

void TestLearningPerceptron::testMetods()
{
	// Тест метода получения доступа к кофиценту обучения
	test_(A.getE() == 1);

	// Тест метода обучения однослойного перцептрона с учителем
	Matrix<double> O(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			O[i][j] = 1;
		}
	}
	Weights<double> OO(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			OO[i][j] = 2;
		}
	}

	A.WTSimplePerceptron(1, -1, OO, O);
	test_(O[0][0] == 1);
	test_(O[0][1] == 1);
	test_(O[0][2] == 1);

	test_(O[1][0] == 1);
	test_(O[1][1] == 1);
	test_(O[1][2] == 1);

	test_(O[2][0] == 1);
	test_(O[2][1] == 1);
	test_(O[2][2] == 1);

	test_(OO[0][0] == 4);
	test_(OO[0][1] == 4);
	test_(OO[0][2] == 4);

	test_(OO[1][0] == 4);
	test_(OO[1][1] == 4);
	test_(OO[1][2] == 4);

	test_(OO[2][0] == 4);
	test_(OO[2][1] == 4);
	test_(OO[2][2] == 4);

	// Тест вычисления квадратичной ошибки
	double yr[] = { 1,2,3 };
	double yyr[] = { 1,2,4 };
	test_(A.RMS_error(yr, yyr, 3) == 0.5);

	// Тест вычисления частной производной квадратичной ошибки
	test_(A.PartDOutLay(yr[2], yyr[2]) == -2);

	// Тест обратного распространения ошибки
	Matrix<double> UUU(2, 2);
	UUU[0][0] = 1;
	UUU[0][1] = 1;
	UUU[1][0] = 1;
	UUU[1][1] = 1;

	Matrix<Weights<double>> II(2,2);
	Weights<double> IIu(2, 2);
	Matrix<double> III(2, 2);
	III[0][0] = 1;
	III[0][1] = 1;
	III[1][0] = 1;
	III[1][1] = 1;

	IIu[0][0] = 1;
	IIu[0][1] = 1;
	IIu[1][0] = 0;
	IIu[1][1] = 0;

	IIu.GetD() = 0.5;
	A.BackPropagation(II,IIu);
	test_(II[0][0].GetD() == 0.5);
	test_(II[0][1].GetD() == 0.5);
	test_(II[1][0].GetD() == 0);
	test_(II[1][1].GetD() == 0);
	
	// Тест градиентного спуска
	SigmD F(0.5);

	A.GradDes(IIu, III, F, 4);
	test_(IIu[0][0] <= 1.5);
	test_(IIu[0][1] <= 1.5);
	test_(IIu[1][0] <= 4);
	test_(IIu[1][1] <= 4);
}

void TestLearningPerceptron::testExeptions()
{

}

TestLearningPerceptron::~TestLearningPerceptron()
{
}
