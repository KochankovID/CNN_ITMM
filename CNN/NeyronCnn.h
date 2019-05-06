#pragma once
#include "Base_Cnn.h"
#include <string>


template<typename T>
class Neyron�nn : public Base_Cnn<T>
{
public:
	// ������������ ----------------------------------------------------------
	Neyron�nn();
	explicit Neyron�nn(const int& step_ );
	Neyron�nn(const Neyron�nn<T>& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	 // �������� ������� ��� �������� ��������
	Matrix<T> Svertka(const Matrix<T>& F, const Matrix<T>& a);

	// ��������� ������� � ���� �������
	int& GetStep() { return step; }

	// ���������� ���������� -------------------------------------------------
	Neyron�nn& operator= (const Neyron�nn<T>& copy) = delete; // ������ �����������
	
	// ���������� ------------------------------------------------------------
	~Neyron�nn();

	// ����� ���������� ------------------------------------------------------
	class Neyron�nnExeption : public Base_Cnn<T>::Base_CnnExeption {
	public:
		Neyron�nnExeption(std::string str) : Base_Cnn<T>::Base_CnnExeption(str) {};
		~Neyron�nnExeption() {};
	};
private:
	// ���� ������ -----------------------------------------------------------
	int step; // ��� �������
};


template<typename T>
Neyron�nn<T>::Neyron�nn() : Base_Cnn<T>(), step(1)
{
}

template<typename T>
Neyron�nn<T>::Neyron�nn(const int& step_) : Base_Cnn<T>(), step(step_)
{
}


template<typename T>
Matrix<T> Neyron�nn<T>::Svertka(const Matrix<T>& F, const Matrix<T>& a)
{

	if ((step > a.getN()) || (step > a.getM())||(step < 1)) {
		throw Neyron�nnExeption("����� ����������� ��� �������!");
	}

	Matrix<T> rez((a.getN() - F.getN()) / step + 1, (a.getM() - F.getM()) / step + 1);

	double sum;
	Matrix<T> fokus;
	for (int i = 0; i < rez.getN(); i++) {
		for (int j = 0; j < rez.getM(); j++) {
			sum = 0;
			fokus = a.getPodmatrix(i*step, j*step, F.getN(), F.getM());
			for (int ii = 0; ii < F.getN(); ii++) {
				for (int jj = 0; jj < F.getM(); jj++) {
					sum += fokus[ii][jj] * F[ii][jj];
				}
			}
			rez[i][j] = sum;
		}
	}
	return rez;
}


template<typename T>
Neyron�nn<T>::~Neyron�nn()
{
}
