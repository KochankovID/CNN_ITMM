#pragma once
#include "Weights.h"
#include "NeyronPerceptron.h"
#include <cstdlib>

template<typename T, typename Y>
class PerceptronLearning
{
public:
	// Конструкторы ----------------------------------------------------------
	PerceptronLearning(); // По умолчанию
	PerceptronLearning(const double& E_); // Инициализатор
	PerceptronLearning(const NeyronPerceptron<T,Y>& copy) = delete; // Запрет копирования

	// Методы класса ---------------------------------------------------------
	// Обучение однослойного перцептрона методом обратного распространения ошибки
	void WTSimplePerceptron(const Y& a, const Y& y, Weights<T>& w, const Matrix<T>& in);

	// Тасование последовательности
	void shuffle(int* arr, const int& lenth);

	// Метод получения доступа к кофиценту обучения
	double& getE() { return E; };

	// Перегрузка операторов -------------------------------------------------
	PerceptronLearning& operator= (const PerceptronLearning& copy) = delete; // Запрет копирования
	friend std::ostream& operator<<(std::ostream& out, const PerceptronLearning& mat) = delete; // Запрет вывода в поток
	friend std::istream& operator>>(std::istream& out, PerceptronLearning& mat) = delete; // Запрет считывания из потока

	// Деструктор ------------------------------------------------------------
	~PerceptronLearning();

protected:
	// Поля класса ----------------------------------
	double E; // Кофицент обучения
};

template<typename T, typename Y>
inline PerceptronLearning<T,Y>::PerceptronLearning() : E(1)
{
}

template<typename T, typename Y>
inline PerceptronLearning<T, Y>::PerceptronLearning(const double & E_) : E(E_)
{
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::WTSimplePerceptron(const Y & a, const Y & y, Weights<T> & w, const Matrix<T>& in)
{
	T delta = a - y;
	T ii = 0;
	if (delta == 0) {
		return;
	}
	for (int i = 0; i < w.getN(); i++) {
		for (int j = 0; j < w.getM(); j++) {
			ii = w[i][j] + E * delta*in[i][j];
			w[i][j] = ii;
		}
	}
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::shuffle(int * arr, const int & lenth)
{
	srand(time(0));
	int j = 0;
	int tmp = 0;
	for (int i = 0; i < lenth; i++) {
		j = ((double)rand()/INT_MAX*lenth);
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
}

template<typename T, typename Y>
inline PerceptronLearning<T, Y>::~PerceptronLearning()
{
}
