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

	// Методы класса ---------------------------------------------------------
	Filter<T> roate_180() const;

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

template<typename T>
inline Filter<T> Filter<T>::roate_180() const
{
	Filter<T> F(this->n, this->m);
	for (int i = this->n-1; i >= 0; i--) {
		for (int j = this->m-1; j >= 0; j--) {
			F[i][j] = this->arr[this->n-1 - i][this->m-1 - j];
		}
	}
	return F;
}

template <typename T>
Filter<T>::~Filter()
{
}
