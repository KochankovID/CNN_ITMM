#pragma once
#include "Matrix.h"
#include "Filter.h"

template<typename T>
class Base_Cnn
{
public:
	// ������������ ----------------------------------------------------------
	Base_Cnn();
	Base_Cnn(const Base_Cnn& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	 // ���������� "�����" � �������
	virtual void Padding(Matrix<T>&);

	// �������� "���� �������"
	virtual void Pooling(Matrix<T>&, const int&, const int&) = 0;

	// �������� ������� ��� �������� ��������
	virtual void Svertka(const Filter<T>&, Matrix<T>&) = 0;

	// ���������� ���������� -------------------------------------------------
	Neyron�nn& operator= (const Neyron�nn<T>& copy) = delete; // ������ �����������
	friend std::ostream& operator<<(std::ostream& out, const Neyron�nn<T>& mat) = delete; // ������ ������ � �����
	friend std::istream& operator>>(std::istream& out, Neyron�nn<T>& mat) = delete; // ������ ���������� �� ������

	// ���������� ------------------------------------------------------------
	~Base_Cnn();
};

template<typename T>
Base_Cnn<T>::Base_Cnn()
{
}

template<typename T>
Base_Cnn<T>::~Base_Cnn()
{
}

template<typename T>
void Base_Cnn<T>::Pooling(Matrix<T>& a, const int& n_, const int& m_)
{
	if ((n_ < 0) || (m_ < 0) || (n_ > a.getN()) || (m_ > a.getM())) {
		throw Neyron�nn::Neyron�nnExeption("�������� ������ ����!");
	}

	Matrix<T> copy(a.getN() / n_, a.getM() / m_);

	for (int i = 0; i < copy.getN(); i++) {
		for (int j = 0; j < copy.getM(); j++) {
			copy[i][j] = Matrix::Max(a.getPodmatrix(i*n_, j*m_, n_, m_));
		}
	}
	a = copy;
}


template<typename T>
void Base_Cnn<T>::Padding(Matrix<T>& a)
{
	Matrix<T> copy(a.getN() + 2, a.getM() + 2);

	for (int i = 0; i < copy.getN(); i++) {
		for (int j = 0; j < copy.getM(); j++) {
			if ((i == 0) || (j == 0) || (j == (copy.getM() - 1)) || (i == (copy.getN() - 1))) {
				copy[i][j] = 0;
			}
			else {
				copy[i][j] = a[i - 1][j - 1];
			}
		}
	}

	a = copy;
}
