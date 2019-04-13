#pragma once
#include "Matrix.h"

class Weights : public Matrix
{
public:
	// ������������ ----------------------------------------------------------
	Weights(); // �� ���������
	Weights(const int& i_, const int& j_); // ������������� (������� �������)
	Weights(double** arr_, const int& i_, const int& j_); // �������������
	Weights(const Weights& copy); // ����������� 

	// ���������� ------------------------------------------------------------
	~Weights();
};

