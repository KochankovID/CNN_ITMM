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
	CNNLearning(Neyron�nn<T>& neyron_, const int& s_ = 1);

	// ������ ������ ---------------------------------------------------------
	void ReversConvolution(Matrix<Weights<T>>& m, const Weights<T>& w, Filter<T> f);

	// ����� ���������� ------------------------------------------------------
	class CNNLearningExeption : public std::runtime_error {
	public:
		LearningExeption(std::string str) : std::runtime_error(str) {};
		~LearningExeption() {};
	};

	// ���������� ------------------------------------------------------------
	~CNNLearning();
private:
	Neyron�nn<T> neyron;
	int s;
};

template<typename T>
inline CNNLearning<T>::CNNLearning(Neyron�nn<T>& neyron_, const int& s_):neyron(neyron_), s(s_)
{
}

template<typename T>
inline void CNNLearning<T>::ReversConvolution(Matrix<Weights<T>>& m, const Weights<T>& w, Filter<T> f)
{
	if ((w.getN() != m.getN()) || (w.getM() != m.getM())) {
		throw CNNLearningExeption("������������ �������� ������� �������� � ������� �����!");
	}
	Weights<T> copy = w;
	neyron.Padding(copy);
	double sum;
	Matrix<T> fokus;
	for (int i = 0; i < m.getN()-w.getN(); i += s) {
		for (int j = 0; j < m.getM() - w.getM(); j += s) {
			sum = 0;
			fokus = m.getPodmatrix(i, j, w.getN(), w.getM());
		}
	}
}

template<typename T>
inline CNNLearning<T>::~CNNLearning()
{
}
