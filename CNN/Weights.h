#pragma once
#include "Matrix.h"

template<typename T>
class Weights : public Matrix<T>
{
public:
	// Конструкторы ----------------------------------------------------------
	Weights(); // По умолчанию
	Weights(const int& i_, const int& j_); // Инициализатор (нулевая матрица)
	Weights(T** arr_, const int& i_, const int& j_); // Инициализатор
	Weights(const Weights<T>& copy); // Копирования 

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
Weights<T>::Weights(const Weights<T> & copy) : Matrix(copy)
{
}

template<typename T>
Weights<T>::~Weights()
{
}
