#include "TestLerningCNN.h"



void TestLerningCNN::testConstruktors()
{
	test_(A.getE() == 1);
	test_(A.getStep() == 1);
}

void TestLerningCNN::testMetods()
{
	// ���� ��������� ���������� �������� ��������
	A.getE() = 2;
	test_(A.getE() == 2);
	A.getE() = 1;

	// ���� ��������� ���� �������
	A.getStep() = 5;
	test_(A.getStep() == 5);
	A.getStep() = 1;

	A
}

void TestLerningCNN::testExeptions()
{
}

TestLerningCNN::~TestLerningCNN()
{
}
