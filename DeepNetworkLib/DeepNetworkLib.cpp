#include "DeepNetworkLib.h"
#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>
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
// Создание перцептрона
DD_Perceptron Neyron;

// Создание обучателя сети
DD_Leaning Teacher;

// Создание функтора
Sigm F(3.4);
SigmD f(3.4);

// Установка зерна для выдачи рандомных значений

// Количество нейронов первого слоя нейросети
const int w1_count = 100;

// Создание весов нейросети
Matrix<Weights<double>> W(1, w1_count);

Matrix<double> mii(5, 3);

// Создания весов для второго слоя сети
Matrix<Weights<double>> W1(1, 10);

// Массив выходов первого слоя сети
Matrix<double> m(1, w1_count);

double summ; // Переменная суммы
double y[w1_count]; // Переменная выхода сети

void startNeyroset() {
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		W1[0][i] = Weights<double>(1, w1_count);
		for (int j = 0; j < W1[0][i].getN(); j++) {
			for (int p = 0; p < W1[0][i].getM(); p++) {
				W1[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		W1[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}
	for (int i = 0; i < w1_count; i++) {
		W[0][i] = Weights<double>(5, 3);
		for (int j = 0; j < W[0][i].getN(); j++) {
			for (int p = 0; p < W[0][i].getM(); p++) {
				W[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		W[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}
	// Считывание весов
	ifstream fWeights;
	fWeights.open("Weights.txt");
	fWeights >> W;
	fWeights >> W1;
	fWeights.close();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			mii[i][j] = -1;
		}
	}
}

int Neyroset(double ooo[]) {
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
	// Создание перцептрона
	DD_Perceptron Neyron;

	// Создание обучателя сети
	DD_Leaning Teacher;

	// Создание функтора
	Sigm F(3.4);
	SigmD f(3.4);

	// Установка зерна для выдачи рандомных значений

	// Количество нейронов первого слоя нейросети
	const int w1_count = 100;

	// Создание весов нейросети
	Matrix<Weights<double>> W(1, w1_count);

	Matrix<double> mii(5, 3);

	// Создания весов для второго слоя сети
	Matrix<Weights<double>> W1(1, 10);

	// Массив выходов первого слоя сети
	Matrix<double> m(1, w1_count);

	double summ; // Переменная суммы
	double y[w1_count]; // Переменная выхода сети

	srand(time(0));
	for (int i = 0; i < 10; i++) {
		W1[0][i] = Weights<double>(1, w1_count);
		for (int j = 0; j < W1[0][i].getN(); j++) {
			for (int p = 0; p < W1[0][i].getM(); p++) {
				W1[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		W1[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}
	for (int i = 0; i < w1_count; i++) {
		W[0][i] = Weights<double>(5, 3);
		for (int j = 0; j < W[0][i].getN(); j++) {
			for (int p = 0; p < W[0][i].getM(); p++) {
				W[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		W[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}
	// Считывание весов
	ifstream fWeights;
	fWeights.open("Weights.txt");
	fWeights >> W;
	fWeights >> W1;
	fWeights.close();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			mii[i][j] = -1;
		}
	}
	for (int l = 0; l < w1_count; l++) { // Цикл прохода по сети
		summ = Neyron.Summator(mii, W[0][l]); // Получение взвешенной суммы
		m[0][l] = Neyron.FunkActiv(summ, F);
	}
	for (int l = 0; l < 10; l++) { // Цикл прохода по сети
		summ = Neyron.Summator(m, W1[0][l]); // Получение взвешенной суммы
		y[l] = Neyron.FunkActiv(summ, F); // Запись выхода l-того нейрона в массив выходов сети
	}
	int max = 0;
	for (int l = 1; l < 10; l++) { // Получение результатов сети
		if (y[l] > y[max]) {
			max = l;
		}
	}
	return max;
}

void Set(int i, int j) {
	mii[i][j] = 1;
}