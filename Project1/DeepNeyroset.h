#pragma once
#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

// Cигмоида
class Sigm : public DD_Func
{
public:
	Sigm(const double& a_) : DD_Func(), a(a_) {};
	double a;
	double operator()(const double& x) {
		double f = 1;
		const double e = 2.7182818284;
		if (x >= 0) {
			for (int i = 0; i < a*x; i++)
			{
				f *= 1 / e;
			}
		}
		else {
			for (int i = 0; i < abs(a*x); i++)
			{
				f *= e;
			}
		}
		f++;
		return 1 / f;
	}
	~Sigm() {};
};

// Производная сигмоиды
class SigmD : public Sigm
{
public:
	SigmD(const double& a_) : Sigm(a_) {};
	double operator()(const double& x) {
		double f = 1;
		f = Sigm::operator()(x)*(1 - Sigm::operator()(x));
		return f;
	}
	~SigmD() {};
};

class Deepnetwork {
public:
	Deepnetwork();

	int Neyroset(double ooo[]);

	~Deepnetwork();

private:

	// Создание перцептрона
	DD_Perceptron Neyron;

	// Создание обучателя сети
	DD_Leaning Teacher;

	// Создание функтора
	Sigm F;
	SigmD f;

	// Установка зерна для выдачи рандомных значений

	// Количество нейронов первого слоя нейросети
	static const int w1_count = 100;

	// Создание весов нейросети
	Matrix<Weights<double>> W;

	// Создания весов для второго слоя сети
	Matrix<Weights<double>> W1;

	// Массив выходов первого слоя сети
	Matrix<double> m;

	double summ; // Переменная суммы
	double y[w1_count]; // Переменная выхода сети
};