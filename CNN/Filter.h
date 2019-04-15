#pragma once
#include "Matrix.h"

template <typename T>
class Filter : public Matrix<T>
{
public:
	// Конструкторы ----------------------------------------------------------
	Filter(); // По умолчанию
	Filter(const int& i_, const int& j_); // Инициализатор (нулевая матрица)
	Filter(T** arr_, const int& i_, const int& j_); // Инициализатор
	Filter(const Filter<T>& copy); // Копирования 

	// Деструктор ------------------------------------------------------------
	~Filter<T>();
};

template <typename T>
Filter<T>::Filter() : Matrix<T>()
{
}

template <typename T>
Filter<T>::Filter(const int & i_, const int & j_) : Matrix<T>(i_, j_)
{
}

template <typename T>
Filter<T>::Filter(T ** arr_, const int & i_, const int & j_) : Matrix<T>(arr_, i_, j_)
{
}

template <typename T>
Filter<T>::Filter(const Filter<T> & copy) : Matrix<T>(copy)
{
}

template <typename T>
Filter<T>::~Filter()
{
}
