#pragma once
#include "Weights.h"
#include "Filter.h"
#include "NeyronCnn.h"
#include <cstdlib>

template<typename T>
class CNNLearning
{
public:
	// Конструкторы ----------------------------------------------------------
	CNNLearning(const int& s_ = 1, const double& E_ = 1);

	// Методы класса ---------------------------------------------------------
	// Метод обратного распространения ошибки
	void ReversConvolution(Matrix<T>& Dnext, const Matrix<T>& D, const Filter<T>& f);

	// Метод градиентного спуска
	void GradDes(const Matrix<T>& X, const Matrix<T>& D, Filter<T>& F);

	// Получение доступа к шагу свертки
	int& getStep() const { return step; }

	// Метод получения доступа к кофиценту обучения
	double& getE() { return E; };

	// Класс исключения ------------------------------------------------------
	class CNNLearningExeption : public std::runtime_error {
	public:
		LearningExeption(std::string str) : std::runtime_error(str) {};
		~LearningExeption() {};
	};

	// Деструктор ------------------------------------------------------------
	~CNNLearning();
private:
	NeyronСnn<T> neyron;
	int s;
	double E;
};

template<typename T>
inline CNNLearning<T>::CNNLearning(const int& s_, const double& E_):neyron(), s(s_), E(E_)
{
}

template<typename T>
inline void CNNLearning<T>::ReversConvolution(Matrix<T>& Dnext, const Matrix<T>& D, const Filter<T>& f)
{
	if (step < 1) {
		throw NeyronСnnExeption("Задан невозможный шаг свертки!");
	}
	f = f.roate_180();
	Matrix<T> O((D.getN() - 1) / s + f.getN(), (D.getM() - 1) / s + f.getM());
	int stepJ = 0, stepI = 0;
	int ii = 0, jj = 0;
	for (int i = 0; i < O.getN(); i++) {
		stepJ = 0;
		if (stepI) {
			for (int j = 0; j < O.getM(); j++) {
					O[i][j] = D[ii][jj++];
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
	neyron.Padding(O);
	Dnext = neyron.Svertka(f, O);
	f.roate_180();
}

template<typename T>
void CNNLearning<T>::GradDes(const Matrix<T>& X, const Matrix<T>& D, Filter<T>& F) {
	Matrix<T> Delta = neyron.Svertka(X, D);
	for (int i = 0; i < Delta.getN(); i++) {
		for (int j = 0; j < Delta.getM(); j++) {
			F[i][j] += E * D[i][j];
		}
	}
}


template<typename T>
inline CNNLearning<T>::~CNNLearning()
{
}
