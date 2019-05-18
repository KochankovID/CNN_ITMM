#include "DeepNeyroset.h"
#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

Deepnetwork::Deepnetwork() : F(2), f(2), FILTERS(f1_count), FILTERS1(f2_count), WEIGHTS(1, w1_count), WEIGHTS1(1, w2_count), 
	MATRIX_OUT(1, w1_count), IMAGE_1(image_width, image_height), IMAGE_2(f1_count), IMAGE_3(f1_count), IMAGE_4(f2_count),
	IMAGE_5(f2_count), IMAGE_2_D(f1_count), IMAGE_3_D(f1_count), IMAGE_4_D(f2_count), IMAGE_5_D(f2_count)
{
	srand(time(0));
	Teacher.getE() = 0.08;
	TeacherCNN.getE() = 0.0000009;

	// Создание весов фильтров первого слоя
	for (int i = 0; i < f1_count; i++) {
		FILTERS[i] = Filter<double>(filter_width, filter_height);
		for (int j = 0; j < FILTERS[i].getN(); j++) {
			for (int p = 0; p < FILTERS[i].getM(); p++) {
				FILTERS[i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// Создание весов фильтров второго слоя
	for (int i = 0; i < f2_count; i++) {
		FILTERS1[i] = Filter<double>(filter1_width, filter1_height);
		for (int j = 0; j < FILTERS1[i].getN(); j++) {
			for (int p = 0; p < FILTERS1[i].getM(); p++) {
				FILTERS1[i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// Создание весов перового слоя перцептрона
	for (int i = 0; i < w1_count; i++) {
		WEIGHTS[0][i] = Weights<double>(neyron_width, neyron_height);
		for (int j = 0; j < WEIGHTS[0][i].getN(); j++) {
			for (int p = 0; p < WEIGHTS[0][i].getM(); p++) {
				WEIGHTS[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		WEIGHTS[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}

	// Создания весов для второго слоя перцептрона
	for (int i = 0; i < w2_count; i++) {
		WEIGHTS1[0][i] = Weights<double>(neyron1_width, neyron1_height);
		for (int j = 0; j < WEIGHTS1[0][i].getN(); j++) {
			for (int p = 0; p < WEIGHTS1[0][i].getM(); p++) {
				WEIGHTS1[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		WEIGHTS1[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}
	for (int i = 0; i < f1_count; i++) {
		IMAGE_2[i] = Matrix<double>(24, 24);
	}
	for (int i = 0; i < f1_count; i++) {
		IMAGE_3[i] = Matrix<double>(12, 12);
	}
	for (int i = 0; i < f2_count; i++) {
		IMAGE_4[i] = Matrix<double>(10, 10);
	}
	for (int i = 0; i < f2_count; i++) {
		IMAGE_5[i] = Matrix<double>(5, 5);
	}
	for (int i = 0; i < f1_count; i++) {
		IMAGE_2_D[i] = Matrix<double>(24, 24);
	}
	for (int i = 0; i < f1_count; i++) {
		IMAGE_3_D[i] = Matrix<double>(12, 12);
	}
	for (int i = 0; i < f2_count; i++) {
		IMAGE_4_D[i] = Matrix<double>(10, 10);
	}
	for (int i = 0; i < f2_count; i++) {
		IMAGE_5_D[i] = Matrix<double>(5, 5);
	}
	//Считывание весов
	ifstream fWeights;
	fWeights.open("Weights.txt");
	for (int i = 0; i < f1_count; i++) {
		fWeights >> FILTERS[i];
	}
	for (int i = 0; i < f2_count; i++) {
		fWeights >> FILTERS1[i];
	}
	fWeights >> WEIGHTS;
	fWeights >> WEIGHTS1;
	fWeights.close();

}

pair<int,int> Deepnetwork::Neyroset(int& rez)
{
	// Создание тестовой выборки
	Matrix<double> TestNums;
	ifstream inputt("Image.txt");
	// Считывание тестовой выборки
	inputt >> TestNums;
	inputt.close();
	int max = 0;
	Matrix<double> NULL_M(28,28);
	NULL_M.Fill(-1);
	// Работа сети
	// Считывание картика поданной на вход сети
	// Проход картинки через первый сверточный слой
	for (int i = 0; i < 252; i += 28) {
		for (int j = 0; j < 252; j += 28) {
			IMAGE_1 = TestNums.getPodmatrix(i,j,28,28);
			max = 0;
			if (IMAGE_1 == NULL_M) {
				continue;
			}
			for (int ii = 0; ii < 10; ii++) {
				y[ii] = 0;
			}
			for (int l = 0; l < f1_count; l++) {
				IMAGE_2[l] = NeyronCNN.Svertka(FILTERS[l], IMAGE_1);
			}
			// Операция макспулинга
			for (int l = 0; l < f1_count; l++) {
				IMAGE_3[l] = NeyronCNN.Pooling(IMAGE_2[l], 2, 2);
			}
			// Проход картинки через второй сверточный слой
			for (int l = 0; l < f1_count; l++) {
				for (int ll = 0; ll < k; ll++) {
					IMAGE_4[l*k + ll] = NeyronCNN.Svertka(FILTERS1[l*k + ll], IMAGE_3[l]);
				}
			}
			// Операция макспулинга
			for (int l = 0; l < f2_count; l++) {
				IMAGE_5[l] = NeyronCNN.Pooling(IMAGE_4[l], 2, 2);
			}
			// Проход по перцептрону
			// Проход по первому слою
			for (int l = 0; l < w1_count; l++) { // Цикл прохода по сети
				summ = Neyron.Summator(IMAGE_5[l], WEIGHTS[0][l]); // Получение взвешенной суммы
				MATRIX_OUT[0][l] = Neyron.FunkActiv(summ, F);
			}
			for (int l = 0; l < w2_count; l++) { // Цикл прохода по сети
				summ = Neyron.Summator(MATRIX_OUT, WEIGHTS1[0][l]); // Получение взвешенной суммы
				y[l] = Neyron.FunkActiv(summ, F); // Запись выхода l-того нейрона в массив выходов сети
			}
			for (int l = 1; l < w2_count; l++) { // Получение результатов сети
				if (y[l] > y[max]) {
					max = l;
				}
			}
			if (y[max] > 0.6) {
				rez = max;
				ofstream out("Text.txt");
				out << IMAGE_1;
				return pair<int, int> (i,j);
			}
		}
	}
	return pair<int, int>(0, 0);
}
	Deepnetwork::~Deepnetwork()
	{
	}
