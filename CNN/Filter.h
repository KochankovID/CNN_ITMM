#pragma once
#include "Matrix.h"

template <typename T>
class Filter : public Matrix<T>
{
public:
	// ������������ ----------------------------------------------------------
	Filter(); // �� ���������
	Filter(const int& i_, const int& j_); // ������������� (������� �������)
	Filter(T** arr_, const int& i_, const int& j_); // �������������
	Filter(const Filter<T>& copy); // ����������� 

	// ���������� ------------------------------------------------------------
	~Filter<T>();
};

template <typename T>
Filter<T>::Filter() : Matrix<T>()
{
}

template <typename T>
Filter<T>::Filter(const int & i_, const int & j_) : Matrix<T>(i_, j_)
{
}

template <typename T>
Filter<T>::Filter(T ** arr_, const int & i_, const int & j_) : Matrix<T>(arr_, i_, j_)
{
}

template <typename T>
Filter<T>::Filter(const Filter<T> & copy) : Matrix<T>(copy)
{
}

template <typename T>
Filter<T>::~Filter()
{
}
