#pragma once
#include "Matrix.h"
class Filter : public Matrix
{
public:
	// ������������ ----------------------------------------------------------
	Filter(); // �� ���������
	Filter(const int& i_, const int& j_); // ������������� (������� �������)
	Filter(double** arr_, const int& i_, const int& j_); // �������������
	Filter(const Filter& copy); // ����������� 

	// ���������� ------------------------------------------------------------
	~Filter();
};

