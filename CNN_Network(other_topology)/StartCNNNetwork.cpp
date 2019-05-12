//: ��������� ������������ ��� �����

#include <Windows.h>
#include "Perceptrons.h"
#include "CNNs.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
// ������ ������ ������ ��������� (� ��������� ��� ���)
#define Teach
#define OUT (X) std::cout << X;

// ��������� ������������� ���������
#define NUMBER nums[j]

// �������
// ��������
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

// ����������� ��������
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

using namespace std;

int main()
{
	// �������� �����������
	DD_Perceptron Neyron;

	// �������� ��������� ����
	DD_Leaning Teacher;
	Teacher.getE() = 0.08;

	// �������� CNN
	D_NeyronCnn NeyronCNN;

	// �������� ��������� CNN ����
	D_CNNLeaning TeacherCNN;
	TeacherCNN.getE() = 0.0000008;

	// �������� ��������
	Sigm F(2);

	// ����������� ��������
	SigmD f(2);

	// ��������� ����� ��� ������ ��������� ��������
	srand(time(0));

	// ������ ������� �������
	const int image_width = 28;
	const int image_height = 28;

	// ������ �������� (���� �������)
	const int filter_width = 5;
	const int filter_height = 5;
	const int filter1_width = 3;
	const int filter1_height = 3;

	// ������ ������� �������� 
	const int neyron_width = 5;
	const int neyron_height = 5;
	const int neyron1_width = 1;
	const int neyron1_height = 100; //50

	// ���������� ��������
	const int f1_count = 10; //5
	const int k = 10;
	const int f2_count = f1_count * k;

	// ���������� ��������
	const int w1_count = 100; //50
	const int w2_count = 10;

	// �������� ����� �������� ������� ����
	vector<Filter<double>> FILTERS(f1_count);
	for (int i = 0; i < f1_count; i++) {
		FILTERS[i] = Filter<double>(filter_width, filter_height);
		for (int j = 0; j < FILTERS[i].getN(); j++) {
			for (int p = 0; p < FILTERS[i].getM(); p++) {
				FILTERS[i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// �������� ����� �������� ������� ����
	vector<Filter<double>> FILTERS1(f2_count);
	for (int i = 0; i < f2_count; i++) {
		FILTERS1[i] = Filter<double>(filter1_width, filter1_height);
		for (int j = 0; j < FILTERS1[i].getN(); j++) {
			for (int p = 0; p < FILTERS1[i].getM(); p++) {
				FILTERS1[i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// �������� ����� �������� ���� �����������
	Matrix<Weights<double>> WEIGHTS(1, w1_count);
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
	Matrix<Weights<double>> WEIGHTS1(1, w2_count);
	for (int i = 0; i < w2_count; i++) {
		WEIGHTS1[0][i] = Weights<double>(neyron1_width, neyron1_height);
		for (int j = 0; j < WEIGHTS1[0][i].getN(); j++) {
			for (int p = 0; p < WEIGHTS1[0][i].getM(); p++) {
				WEIGHTS1[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		WEIGHTS1[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}

	// ������� ������ ����
	Matrix<double> MATRIX_OUT(1, w1_count);

	double summ; // ���������� �����
	double y[w2_count]; // ���������� ������ ����

	// ������� �����������
	Matrix<double> IMAGE_1(image_width, image_height);
	vector< Matrix<double>> IMAGE_2(f1_count);
	for (int i = 0; i < f1_count; i++) {
		IMAGE_2[i] = Matrix<double>(24, 24);
	}

	vector< Matrix<double>> IMAGE_3(f1_count);
	for (int i = 0; i < f1_count; i++) {
		IMAGE_3[i] = Matrix<double>(12, 12);
	}

	vector< Matrix<double>> IMAGE_4(f2_count);
	for (int i = 0; i < f2_count; i++) {
		IMAGE_4[i] = Matrix<double>(10, 10);
	}

	vector< Matrix<double>> IMAGE_5(f2_count);
	for (int i = 0; i < f2_count; i++) {
		IMAGE_5[i] = Matrix<double>(5, 5);
	}

#ifdef Teach
	// ������� ������ ���������� ����
	vector< Matrix<double>> IMAGE_2_D(f1_count);
	for (int i = 0; i < f1_count; i++) {
		IMAGE_2_D[i] = Matrix<double>(24, 24);
	}

	vector< Matrix<double>> IMAGE_3_D(f1_count);
	for (int i = 0; i < f1_count; i++) {
		IMAGE_3_D[i] = Matrix<double>(12, 12);
	}

	vector< Matrix<double>> IMAGE_4_D(f2_count);
	for (int i = 0; i < f2_count; i++) {
		IMAGE_4_D[i] = Matrix<double>(10, 10);
	}

	vector< Matrix<double>> IMAGE_5_D(f2_count);
	for (int i = 0; i < f2_count; i++) {
		IMAGE_5_D[i] = Matrix<double>(5, 5);
	}


	// ������������������ ����, �������� ��� ��������� ����������� ������������
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

	// �������� ��������� �������
	vector<vector<Matrix<double>>> Nums(10);
	for (int i = 0; i < 10; i++) {
		Nums[i] = vector<Matrix<double>>(10);
	}
	// ���������� ��������� �������
	string folder;
	string file = "TeachChoose.txt";
	string path;
	ifstream input(file);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 1; j++) {
			input >> Nums[i][j];
		}
	}
	input.close();
	// �������� ����
	long int koll = 10; // ���������� �������� ���������

	for (long int i = 1; i < koll; i++) {
		cout << i << endl;
		for (int j = 0; j < 10; j++) { // ���� ������� �� ��������� �������
			cout << "	a)" << j << endl;
			for (int u = 0; u < 3; u++) {
				cout << "		b)" << u << endl;
				for (int ooo = 0; ooo < 1; ooo++) {
					cout << "			c)" << ooo << endl;
					// ������ ����
					// ���������� ������� �������� �� ���� ����
					IMAGE_1 = Nums[NUMBER][ooo];
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
					// �������� ����
					for (int l = 0; l < w2_count; l++) { // ������ ������ ��� ��������� ����
						if (l == NUMBER) { // ���� ����� ������� ��������� � �������� �� ���� ������, �� ���������� ����� 1
							WEIGHTS1[0][l].GetD() = Teacher.PartDOutLay(1, y[l]); // ������ ������
						}
						else {// ���� ����� ������� ��������� � �������� �� ���� ������, �� ���������� ����� 1
							WEIGHTS1[0][l].GetD() = Teacher.PartDOutLay(0, y[l]); // ������ ������
						}
					}
					// ��������������� ������ �� ������� ���� ���������
					for (int l = 0; l < w2_count; l++) {
						Teacher.BackPropagation(WEIGHTS, WEIGHTS1[0][l]);
					}
					// ����������� ������ �� ������������� ����
					for (int l = 0; l < f2_count; l++) {
						IMAGE_5_D[l].Fill(WEIGHTS[0][l].GetD());
					}
					// ��������������� ������ �� ���������� ����
					for (int l = 0; l < f2_count; l++) {
						IMAGE_4_D[l] = TeacherCNN.ReversPooling(IMAGE_5_D[l], 2, 2);
					}
					// ��������������� ������ �� ������������� ����
					for (int l = 0; l < f1_count; l++) {
						IMAGE_3_D[l] = TeacherCNN.ReversConvolution(IMAGE_4_D[l*k], FILTERS1[l*k]);
						for (int ll = 1; ll < k; ll++) {
							IMAGE_3_D[l] = IMAGE_3_D[l] + TeacherCNN.ReversConvolution(IMAGE_4_D[l*k + ll], FILTERS1[l*k + ll]);
						}
					}
					// ��������������� ������ �� ���������� ����
					for (int l = 0; l < f1_count; l++) {
						IMAGE_2_D[l] = TeacherCNN.ReversPooling(IMAGE_3_D[l], 2, 2);
					}
					// ���������� ������������ ������ 

					// ������ ���������� ����
					for (int l = 0; l < f1_count; l++) {
						TeacherCNN.GradDes(IMAGE_1, IMAGE_2_D[l], FILTERS[l]);
					}
					// ������ ���������� ����
					for (int l = 0; l < f1_count; l++) {
						for (int ll = 0; ll < k; ll++) {
							TeacherCNN.GradDes(IMAGE_3[l], IMAGE_4_D[l*k + ll], FILTERS1[l*k + ll]);
						}
					}
					// ����������
					// ������ ����
					for (int l = 0; l < w1_count; l++) { // ���������� ������������ ������ �� ���� ��������� ������� ����
						Teacher.GradDes(WEIGHTS[0][l], IMAGE_5[l], f, MATRIX_OUT[0][l]);
					}

					// ������ ����
					for (int l = 0; l < w2_count; l++) { // ���������� ������������ ������ �� ���� ��������� ������� ����
						summ = Neyron.Summator(MATRIX_OUT, WEIGHTS1[0][l]);
						Teacher.GradDes(WEIGHTS1[0][l], MATRIX_OUT, f, summ);
					}
					// ��������� ������
					for (int l = 0; l < w1_count; l++) { // ��������� ������ �������� 1 ����
						WEIGHTS[0][l].GetD() = 0;
					}
				}
				Teacher.retract(WEIGHTS, 3);
				Teacher.retract(WEIGHTS1, 3);

				double a[10];
				for (int i = 0; i < w2_count; i++) {
					if (i == NUMBER)
						a[i] = 1;
					if (i != NUMBER)
						a[i] = 0;
				}
				cout << Teacher.RMS_error(a, y, w2_count) << endl;

			}
		}
	}

	// ��������� ����
	ofstream fWeights;
	fWeights.open("Weights.txt");
	for (int i = 0; i < f1_count; i++) {
		fWeights << FILTERS[i];
	}
	for (int i = 0; i < f2_count; i++) {
		fWeights << FILTERS1[i];
	}
	fWeights << WEIGHTS;
	fWeights << WEIGHTS1;
	fWeights.close();

#else
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
	string folder;
	string file;
	string path;

#endif // Teach

	// �������� �������� �������
	vector<vector<Matrix<double>>> TestNums(10);
	for (int i = 0; i < 10; i++) {
		TestNums[i] = vector<Matrix<double>>(10);
	}
	// ���������� �������� �������
	folder = "..\\Image_to_txt\\";
	for (int i = 0; i < 10; i++) {
		file = to_string(i) + ".txt";
		path = folder + file;
		ifstream inputt(path);
		for (int j = 0; j < 10; j++) {
			inputt >> TestNums[i][j];
		}
		inputt.close();
	}
	int max = 0;
	// ����� �� ����� ���������� ������������ ����
	cout << "Test network:" << endl;
	for (int i = 0; i < 10; i++) { // ���� ������� �� �������� �������
		for (int j = 0; j < 10; j++) {
			int max = 0;
			// ������ ����
			// ���������� ������� �������� �� ���� ����
			IMAGE_1 = TestNums[i][j];
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
			cout << "Test " << i << " : " << "recognized " << max << ' ' << y[max] << endl;
		}
	}

	// ���������� �������� �������
	file = "Tests.txt";
	ifstream inputtt(file);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 1; j++) {
			inputtt >> TestNums[i][j];
		}
	}

	// ����� �� ����� ���������� ������������ ����
	cout << "Test network:" << endl;
	for (int i = 0; i < 10; i++) { // ���� ������� �� �������� �������
		int max = 0;
		// ������ ����
		// ���������� ������� �������� �� ���� ����
		IMAGE_1 = TestNums[i][0];
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
		cout << "Test " << i << " : " << "recognized " << max << ' ' << y[max] << endl;
	}
	system("pause");
	return 0;

}