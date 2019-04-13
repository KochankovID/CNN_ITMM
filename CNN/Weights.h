#pragma once
#include "Matrix.h"

class Weights : public Matrix
{
public:
	// Конструкторы ----------------------------------------------------------
	Weights(); // По умолчанию
	Weights(const int& i_, const int& j_); // Инициализатор (нулевая матрица)
	Weights(double** arr_, const int& i_, const int& j_); // Инициализатор
	Weights(const Weights& copy); // Копирования 

	// Деструктор ------------------------------------------------------------
	~Weights();
};

