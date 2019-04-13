#pragma once
#include "Matrix.h"

class NeyronPerceptron : public Matrix
{
public:
	// Конструкторы ----------------------------------------------------------
	NeyronPerceptron();
	NeyronPerceptron(const int& i_, const int& j_);
	NeyronPerceptron(double** arr_, const int& i_, const int& j_);
	NeyronPerceptron(const NeyronPerceptron& copy);

	// Методы класса ---------------------------------------------------------
	// Операция суммированию произведений входов на веса нейрона
	double Summator(double** arr_); 

	// Функция активации нейрона
	double FunkActiv(const double& x, double(*func)(const double&, const double&));

	// Деструктор ------------------------------------------------------------
	~NeyronPerceptron();
};


// Заготовленный функции активации
// Функция единичного скачка
double SingHopFunc(const double& x, const double& b);

// Сигмоидальная функция
double Sigfunc(const double& x, const double& b);

// Гиперболический гангенс
double HyperTang(const double& x, const double&);