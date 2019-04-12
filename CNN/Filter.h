#pragma once
#include "Matrix.h"
class Filter : public Matrix
{
public:
	// Конструкторы ----------------------------------------------------------
	Filter(); // По умолчанию
	Filter(const int& i_, const int& j_); // Инициализатор (нулевая матрица)
	Filter(int** arr_, const int& i_, const int& j_); // Инициализатор
	Filter(const Filter& copy); // Копирования 

	// Деструктор ------------------------------------------------------------
	~Filter();
};

