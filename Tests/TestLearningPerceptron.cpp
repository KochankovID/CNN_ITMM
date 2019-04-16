#include "TestLearningPerceptron.h"
#include "Weights.h"

void TestLearningPerceptron::testConstruktors()
{
	// ���� ����������� �� ���������
	PerceptronLearning<double, double> B;
	test_(B.getE() == 1);

	// ���� ������������ ��������������
	PerceptronLearning<int, int> O(0.4);
	test_(O.getE() == 0.4);
}

void TestLearningPerceptron::testMetods()
{
	// ���� ������ ��������� ������� � ��������� ��������
	test_(A.getE() == 1);

	// ���� ������ �������� ������������ ����������� � ��������
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
}

void TestLearningPerceptron::testExeptions()
{

}

TestLearningPerceptron::~TestLearningPerceptron()
{
}
