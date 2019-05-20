#pragma once
#include <Windows.h>
#include "Perceptrons.h"
#include "CNNs.h"
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
			if (x > 10000) {
				return 0.99999999;
			}
			for (int i = 0; i < a*x; i++)
			{
				f *= 1 / e;
			}
		}
		else {
			if (x < -10000) {
				return 0.00000001;
			}
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

	std::pair<int, int> Neyroset(int& rez);

	~Deepnetwork();

private:

	// Создание перцептрона
	DD_Perceptron Neyron;

	// Создание обучателя сети
	DD_Leaning Teacher;


	// Создание CNN
	D_NeyronCnn NeyronCNN;

	// Создание обучателя CNN сети
	D_CNNLeaning TeacherCNN;


	// Создание функтора
	Sigm F;

	// Производная функтора
	SigmD f;


	// Размер входной матрицы
	static const int image_width = 28;
	static const int image_height = 28;

	// Размер фильтров (ядер свертки)
	static const int filter_width = 5;
	static const int filter_height = 5;
	static const int filter1_width = 3;
	static const int filter1_height = 3;

	// Размер матрицы нейронов 
	static const int neyron_width = 100;
	static const int neyron_height = 4;
	static const int neyron1_width = 1;
	static const int neyron1_height = 50;

	// Количество фильтров
	static const int f1_count = 5; 
	static const int k = 5;
	static const int f2_count = f1_count * k;

	// Количество нейронов
	static const int w1_count = 120;
	static const int w2_count = 10;

	// Матрица выхода сети
	Matrix<double> MATRIX_OUT;

	double summ; // Переменная суммы
	double y[w2_count]; // Переменная выхода сети

	// Создание весов фильтров первого слоя
	std::vector<Filter<double>> FILTERS;

	// Создание весов фильтров второго слоя
	std::vector<Filter<double>> FILTERS1;

	// Создание весов перового слоя перцептрона
	Matrix<Weights<double>> WEIGHTS;

	// Создания весов для второго слоя перцептрона
	Matrix<Weights<double>> WEIGHTS1;


	// Матрица выхода сети
	Matrix<double> IMAGE_OUT;

	// Матрицы изображений
	Matrix<double> IMAGE_1;
	std::vector< Matrix<double>> IMAGE_2;
	std::vector< Matrix<double>> IMAGE_3;
	std::vector< Matrix<double>> IMAGE_4;
	std::vector< Matrix<double>> IMAGE_5;

	// Матрицы ошибок сверточной сети
	std::vector< Matrix<double>> IMAGE_2_D;
	std::vector< Matrix<double>> IMAGE_3_D;
	std::vector< Matrix<double>> IMAGE_4_D;
	std::vector< Matrix<double>> IMAGE_5_D;

	// Последовательность цифр, тасуемая для получения равномерной рандомизации
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

};