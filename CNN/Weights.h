#pragma once
#include "Matrix.h"
#include <iostream>
#include <iomanip>

template<typename T>
class Weights : public Matrix<T>
{
public:
	// Конструкторы ----------------------------------------------------------
	Weights(); // По умолчанию
	Weights(const int& i_, const int& j_); // Инициализатор (нулевая матрица)
	Weights(T** arr_, const int& i_, const int& j_); // Инициализатор
	Weights(const Weights<T>& copy); // Копирования 

	// Методы класса ---------------------------------------------------------
	// Вывод весов на консоль в красивом виде
	void Out();

	// Деструктор ------------------------------------------------------------
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
Weights<T>::Weights(const Weights<T> & copy) : Matrix<T>(copy)
{
}

template<typename T>
inline void Weights<T>::Out()
{
	for (int i = 0; i < this->n; i++) {
		for(int j = 0; j < this->m; j++){
			std::cout << this->arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

inline void Weights<int>::Out()
{
	using std::cout;
	int max = this->Max();
	int k = 2;
	while (max > 0) {
		k++;
		max = max / 10;
	}
	for (int i = 0; i < this->n; i++) {
		for (int j = 0; j < this->m; j++) {
			cout << std::setw(k) << this->arr[i][j];
		}
		cout << std::endl;
	}
}

inline void Weights<double>::Out()
{
	using std::cout;
	int max = (int)this->Max();
	int k = 2;
	while (max > 0) {
		k++;
		max = max / 10;
	}
	for (int i = 0; i < this->n; i++) {
		for (int j = 0; j < this->m; j++) {
			cout << std::setw(k+4) << std::setprecision(4)<< this->arr[i][j];
		}
		cout << std::endl;
	}
}

template<typename T>
Weights<T>::~Weights()
{
}
