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

	// Перегрузки операторов ------------------------
	Filter<T>& operator= (const Filter<T>& copy); // Оператор присваивания
	
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

template<typename T>
inline Filter<T>& Filter<T>::operator=(const Filter<T>& copy)
{
	if (this == &copy) {
		return *this;
	}
	if ((copy.n > this->n) || (copy.m > this->m)) {
		for (int i = 0; i < this->n; i++) {
			this->arr[i].reset();
		}
		this->arr.reset();
		this->n = copy.n;
		this->m = copy.m;
		this->initMat();
	}
	else {
		this->n = copy.n;
		this->m = copy.m;
	}

	for (int i = 0; i < this->n; i++) {
		for (int j = 0; j < this->m; j++) {
			this->arr[i][j] = copy.arr[i][j];
		}
	}
	return *this;
}

template <typename T>
Filter<T>::~Filter()
{
}
