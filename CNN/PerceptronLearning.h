#pragma once
#include "Weights.h"

template<typename T, typename Y>
class PerceptronLearning
{
public:
	// ������������ ----------------------------------------------------------
	PerceptronLearning(); // �� ���������
	PerceptronLearning(const double& E_); // �������������
	PerceptronLearning(const NeyronPerceptron& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	// �������� ������������ ����������� ������� ��������� ��������������� ������
	void WTSimplePerceptron(const Y& a, const Y& y, Weights<T>& w, const Matrix<T> in);

	// ���������� ���������� -------------------------------------------------
	PerceptronLearning& operator= (const PerceptronLearning& copy) = delete; // ������ �����������
	friend std::ostream& operator<<(std::ostream& out, const PerceptronLearning& mat) = delete; // ������ ������ � �����
	friend std::istream& operator>>(std::istream& out, PerceptronLearning& mat) = delete; // ������ ���������� �� ������

	// ���������� ------------------------------------------------------------
	~PerceptronLearning();

protected:
	// ���� ������ ----------------------------------
	double E; // �������� ��������
};

template<typename T, typename Y>
inline PerceptronLearning<T,Y>::PerceptronLearning() : E(1)
{
}

template<typename T, typename Y>
inline PerceptronLearning<T, Y>::PerceptronLearning(const double & E_)
{
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::WTSimplePerceptron(const Y & a, const Y & y, Weights<T> & w, const Matrix<T> in)
{
	T delta = a - y;
	for (int i = 0; i < w.getN(); i++) {
		for (int j = 0; j < w.getM(); j++) {
			w[i] = w[i] + E * d*in[i];
		}
	}
}

template<typename T, typename Y>
inline PerceptronLearning<T, Y>::~PerceptronLearning()
{
}