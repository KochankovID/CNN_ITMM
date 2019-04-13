#pragma once
#include "Matrix.h"
#include "Weights.h"

class NeyronPerceptron
{
public:
	// Конструкторы ----------------------------------------------------------
	NeyronPerceptron();
	NeyronPerceptron(const NeyronPerceptron& copy) = delete; // Запрет копирования

	// Методы класса ---------------------------------------------------------
	// Операция суммированию произведений входов на веса нейрона
	double Summator(Matrix& a, const Weights& w);

	// Функция активации нейрона
	double FunkActiv(const double& x, const double& a, double(*func)(const double&, const double&));

	// Перегрузка операторов -------------------------------------------------
	NeyronPerceptron& operator= (const NeyronPerceptron& copy) = delete; // Запрет копирования
	friend std::ostream& operator<<(std::ostream& out, const NeyronPerceptron& mat) = delete; // Запрет вывода в поток
	friend std::istream& operator>>(std::istream& out, NeyronPerceptron& mat) = delete; // Запрет считывания из потока

	// Деструктор ------------------------------------------------------------
	~NeyronPerceptron();

	// Класс исключения ------------------------------------------------------
	class NeyronPerceptronExeption : public std::runtime_error {
	public:
		NeyronPerceptronExeption(std::string str) : std::runtime_error(str) {};
		~NeyronPerceptronExeption() {};
	};
};


// Заготовленный функции активации
// Функция единичного скачка
double SingHopFunc(const double& x, const double& b);

// Сигмоидальная функция
double Sigfunc(const double& x, const double& b);

// Гиперболический гангенс
double HyperTang(const double& x, const double&);