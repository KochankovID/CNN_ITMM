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

	// �������� ����� �������� ������� ����
	for (int i = 0; i < f1_count; i++) {
		FILTERS[i] = Filter<double>(filter_width, filter_height);
		for (int j = 0; j < FILTERS[i].getN(); j++) {
			for (int p = 0; p < FILTERS[i].getM(); p++) {
				FILTERS[i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// �������� ����� �������� ������� ����
	for (int i = 0; i < f2_count; i++) {
		FILTERS1[i] = Filter<double>(filter1_width, filter1_height);
		for (int j = 0; j < FILTERS1[i].getN(); j++) {
			for (int p = 0; p < FILTERS1[i].getM(); p++) {
				FILTERS1[i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// �������� ����� �������� ���� �����������
	for (int i = 0; i < w1_count; i++) {
		WEIGHTS[0][i] = Weights<double>(neyron_width, neyron_height);
		for (int j = 0; j < WEIGHTS[0][i].getN(); j++) {
			for (int p = 0; p < WEIGHTS[0][i].getM(); p++) {
				WEIGHTS[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		WEIGHTS[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}

	// �������� ����� ��� ������� ���� �����������
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
	//���������� �����
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

int Deepnetwork::Neyroset()
{
	// �������� �������� �������
	Matrix<double> TestNums;
	ifstream inputt("Image.txt");
	// ���������� �������� �������
	inputt >> TestNums;
	inputt.close();
	// ������ ����
	// ���������� ������� �������� �� ���� ����
	// ������ �������� ����� ������ ���������� ����
	int max = 0;
	// ������ ����
	// ���������� ������� �������� �� ���� ����
	IMAGE_1 = TestNums;
	// ������ �������� ����� ������ ���������� ����
	for (int l = 0; l < f1_count; l++) {
		IMAGE_2[l] = NeyronCNN.Svertka(FILTERS[l], IMAGE_1);
	}
	// �������� �����������
	for (int l = 0; l < f1_count; l++) {
		IMAGE_3[l] = NeyronCNN.Pooling(IMAGE_2[l], 2, 2);
	}
	// ������ �������� ����� ������ ���������� ����
	for (int l = 0; l < f1_count; l++) {
		for (int ll = 0; ll < k; ll++) {
			IMAGE_4[l*k + ll] = NeyronCNN.Svertka(FILTERS1[l*k + ll], IMAGE_3[l]);
		}
	}
	// �������� �����������
	for (int l = 0; l < f2_count; l++) {
		IMAGE_5[l] = NeyronCNN.Pooling(IMAGE_4[l], 2, 2);
	}
	// ������ �� �����������
	// ������ �� ������� ����
	for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
		summ = Neyron.Summator(IMAGE_5[l], WEIGHTS[0][l]); // ��������� ���������� �����
		MATRIX_OUT[0][l] = Neyron.FunkActiv(summ, F);
	}
	for (int l = 0; l < w2_count; l++) { // ���� ������� �� ����
		summ = Neyron.Summator(MATRIX_OUT, WEIGHTS1[0][l]); // ��������� ���������� �����
		y[l] = Neyron.FunkActiv(summ, F); // ������ ������ l-���� ������� � ������ ������� ����
	}
	for (int l = 1; l < w2_count; l++) { // ��������� ����������� ����
		if (y[l] > y[max]) {
			max = l;
		}
	}
		return max;
}
	Deepnetwork::~Deepnetwork()
	{
	}
