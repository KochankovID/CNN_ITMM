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
	void Svertka(const Filter<T>& F, Matrix<T>& a);

	// ��������� ���� �������
	int GetStep() const { return step; }

	// ��������� ���� �������
	void SetStep(const int& step_)
	{
		if (step_ < 0) {
			throw Neyron�nnExeption("����� ����������� ��� �������!");
		}
		step = step_;
	}

	// ���������� ���������� -------------------------------------------------
	Neyron�nn& operator= (const Neyron�nn<T>& copy) = delete; // ������ �����������
	
	// ���������� ------------------------------------------------------------
	~Neyron�nn();

	// ����� ���������� ------------------------------------------------------
	class Neyron�nnExeption : public std::runtime_error {
	public:
		Neyron�nnExeption(std::string str) : std::runtime_error(str) {};
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
void Neyron�nn<T>::Svertka(const Filter<T>& F, Matrix<T>& a)
{

	if ((step > a.getN()) || (step > a.getM())) {
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
	a = rez;
}


template<typename T>
Neyron�nn<T>::~Neyron�nn()
{
}
