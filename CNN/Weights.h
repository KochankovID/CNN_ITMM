#pragma once
#include "Matrix.h"
#include <iostream>
#include <iomanip>

template<typename T>
class Weights : public Matrix<T>
{
public:
	// ������������ ----------------------------------------------------------
	Weights(); // �� ���������
	Weights(const int& i_, const int& j_); // ������������� (������� �������)
	Weights(T** arr_, const int& i_, const int& j_); // �������������
	Weights(const Weights<T>& copy); // ����������� 

	// ������ ������ ---------------------------------------------------------
	// ����� ����� �� ������� � �������� ����
	void Out();

	// ���������� ------------------------------------------------------------
	~Weights();
};

template<typename T>
Weights<T>::Weights() : Matrix<T>()
{
}

template<typename T>
Weights<T>::Weights(const int & i_, const int & j_) : Matrix<T>(i_, j_)
{
}

template<typename T>
Weights<T>::Weights(T ** arr_, const int & i_, const int & j_) : Matrix<T>(arr_, i_, j_)
{
}

template<typename T>
Weights<T>::Weights(const Weights<T> & copy) : Matrix(copy)
{
}

template<typename T>
inline void Weights<T>::Out()
{
	using std::cout;
	T max = this->Max();
	int k = 2;
	while (max > 0) {
		k++;
		max = max / 10;
	}
	for (int i = 0; i < this->n; i++) {
		for(int j = 0; j < this->m; j++){
			cout << std::setw(k) << this->arr[i][j];
		}
		cout << std::endl;
	}
}

template<typename T>
Weights<T>::~Weights()
{
}
