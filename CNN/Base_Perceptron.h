#pragma once
#include "Matrix.h"
#include "Weights.h"
#include <vector>


template <typename T, typename Y>
class Base_Perceptron
{
	// Конструкторы ----------------------------------------------------------
	Base_Perceptron();
	Base_Perceptron(const Base_Perceptron& copy) = delete; // Запрет копирования

	// Методы класса ---------------------------------------------------------
	// Операция суммированию произведений входов на веса нейрона
	virtual T Summator(Matrix<T>& a, const Weights<T>& w);
	virtual T Summator(std::vector<T> a, const std::vector<T>& w);

	// Функция активации нейрона
	virtual Y FunkActiv(const T&, Func<Y>) = 0;

	// Перегрузка операторов -------------------------------------------------
	NeyronPerceptron& operator= (const NeyronPerceptron& copy) = delete; // Запрет копирования
	
	// Деструктор ------------------------------------------------------------
	~Base_Perceptron();

	// Класс исключения ------------------------------------------------------
	class NeyronPerceptronExeption : public std::runtime_error {
	public:
		NeyronPerceptronExeption(std::string str) : std::runtime_error(str) {};
		~NeyronPerceptronExeption() {};
	};
};

template <typename T, typename Y>
Base_Perceptron<T, Y>::Base_Perceptron()
{
}

template <typename T, typename Y>
T Base_Perceptron<T, Y>::Summator(Matrix<T> & a, const Weights<T> & w)
{
	if ((a.getN() != w.getN()) || (a.getM() != w.getM())) {
		throw NeyronPerceptron::NeyronPerceptronExeption("Несовпадение размера матрицы весов и размера матрицы входных сигналов!");
	}
	T sum = 0;
	for (int i = 0; i < a.getN(); i++) {
		for (int j = 0; j < a.getM(); j++) {
			sum += a[i][j] * w[i][j];
		}
	}
	return sum;
}

template <typename T, typename Y>
inline T Base_Perceptron<T, Y>::Summator(std::vector<T> a, const std::vector<T>& w)
{
	if ((a.getN() != w.getN()) || (a.getM() != w.getM())) {
		throw NeyronPerceptron::NeyronPerceptronExeption("Несовпадение размера матрицы весов и размера матрицы входных сигналов!");
	}
	T sum = 0;
	for (int i = 0; i < a.size(); i++) {
		T = a[i] * w[i];
	}
	return sum;
}

template <typename T, typename Y>
Base_Perceptron<T,Y>::~Base_Perceptron()
{
}