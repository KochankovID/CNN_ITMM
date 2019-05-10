#pragma once
#include "Weights.h"
#include "Filter.h"
#include "NeyronCnn.h"
#include <cstdlib>

template<typename T>
class CNNLearning
{
public:
	// ������������ ----------------------------------------------------------
	CNNLearning(const int& s_ = 1, const double& E_ = 1);

	// ������ ������ ---------------------------------------------------------
	// ����� ��������� ��������������� ������
	Matrix<T> ReversConvolution(const Matrix<T>& D, const Filter<T>& f);

	// ����� ������������ ������
	void GradDes(const Matrix<T>& X, const Matrix<T>& D, Filter<T>& F);

	// ��������� ������� � ���� �������
	int& getStep() { return s; }

	// ����� ��������� ������� � ��������� ��������
	double& getE() { return E; };

	// �������� ��������� ��������������� ������ �� ���� "���� �������"
	Matrix<T> ReversPooling(const Matrix<T>& a, const int& n_, const int& m_);

	// ����� ���������� ------------------------------------------------------
	class CNNLearningExeption : public std::runtime_error {
	public:
		CNNLearningExeption(std::string str) : std::runtime_error(str) {};
		~CNNLearningExeption() {};
	};

	// ���������� ------------------------------------------------------------
	~CNNLearning();
private:
	Neyron�nn<T> neyron;
	int s;
	double E;
};

template<typename T>
inline CNNLearning<T>::CNNLearning(const int& s_, const double& E_):neyron(), s(s_), E(E_)
{
}

template<typename T>
inline Matrix<T> CNNLearning<T>::ReversConvolution(const Matrix<T>& D, const Filter<T>& f)
{
	if (s < 1) {
			throw CNNLearning<T>::CNNLearningExeption("����� ����������� ��� �������!");
	}
	auto F = f.roate_180();
	Matrix<T> O((D.getN() - 1) / s + f.getN(), (D.getM() - 1) / s + f.getM());
	if (s != 1) {
		int stepJ = 0, stepI = 0;
		int ii = 0, jj = 0;
		for (int i = 0; i < O.getN(); i++) {
			stepJ = 0;
			if (stepI) {
				for (int j = 0; j < O.getM(); j++) {
					O[i][j] = 0;
				}
				stepI--;
			}
			else {
				for (int j = 0; j < O.getM(); j++) {
					if (stepJ) {
						stepJ--;
						O[i][j] = 0;
					}
					else {
						O[i][j] = D[ii][jj++];
						stepJ = s;
					}
				}
				stepI = s;
			}
		}
	}
	else {
		O = D;
	}
	for (int i = 0; i < f.getN()-1; i++) {
		neyron.Padding(O);
	}
	return neyron.Svertka(F, O);
}

template<typename T>
void CNNLearning<T>::GradDes(const Matrix<T>& X, const Matrix<T>& D, Filter<T>& F) {
	Matrix<T> Delta = neyron.Svertka(D, X);
	if ((Delta.getN() != F.getN()) || (Delta.getM() != F.getM())) {
		throw CNNLearning<T>::CNNLearningExeption("������ �������� �����������! ����� ������� ������� ������� ������� � ������� ������ �� ���������!");
	}
	for (int i = 0; i < Delta.getN(); i++) {
		for (int j = 0; j < Delta.getM(); j++) {
			F[i][j] += E * Delta[i][j];
		}
	}
}

template<typename T>
inline Matrix<T> CNNLearning<T>::ReversPooling(const Matrix<T>& D, const int & n_, const int & m_)
{
	if ((n_ < 0) || (m_ < 0) || (n_ > D.getN()) || (m_ > D.getM())) {
		throw Base_Cnn<T>::Base_CnnExeption("�������� ������ ����!");
	}

	Matrix<T> copy(D.getN() * n_, D.getM() * m_);

	for (int i = 0; i < D.getN(); i++) {
		for (int j = 0; j < D.getM(); j++) {
			for (int ii = i * n_; ii < i*n_ + n_; ii++) {
				for (int jj = j * m_; jj < j*m_ + m_; jj++) {
					copy[ii][jj] = D[i][j];
				}
			}
		}
	}
	return copy;
}


template<typename T>
inline CNNLearning<T>::~CNNLearning()
{
}
