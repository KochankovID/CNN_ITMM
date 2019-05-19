//: ��������� ������������ ��� �����

#include <Windows.h>
#include "Perceptrons.h"
#include "CNNs.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;
// ������ ������ ������ ��������� (� ��������� ��� ���)
#define Teach

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
	Teacher.getE() = 0.02048;

	// �������� CNN
	D_NeyronCnn NeyronCNN;

	// �������� ��������� CNN ����
	D_CNNLeaning TeacherCNN;
	TeacherCNN.getE() = 0.000000009;

	// �������� ��������
	Sigm F(1.6);

	// ����������� ��������
	SigmD f(1.6);

	// ��������� ����� ��� ������ ��������� ��������
	srand(time(0));

	// ������ ������� �������
	const int image_width = 28;
	const int image_height = 28;

	// ������ �������� (���� �������)
	const int filter_width = 5;
	const int filter_height = 5;
	const int filter1_width = 5;
	const int filter1_height = 5;

	// ������ ������� �������� 
	const int neyron_width = 36;
	const int neyron_height = 4;
	const int neyron1_width = 120;
	const int neyron1_height = 1; 

	// ���������� ��������
	const int f1_count = 3;
	const int k = 3;
	const int f2_count = f1_count * k;

	// ���������� ��������
	const int w1_count = 120;
	const int w2_count = 10;
	
	// �������� �������� �����
	const int wwww = 1;

	// �������� ����� �������� ������� ����
	vector<Filter<double>> FILTERS(f1_count);
	for (int i = 0; i < f1_count; i++) {
		FILTERS[i] = Filter<double>(filter_height, filter_width);
		for (int j = 0; j < FILTERS[i].getN(); j++) {
			for (int p = 0; p < FILTERS[i].getM(); p++) {
				FILTERS[i][j][p] = (p % 2 ? ((double)rand() / (RAND_MAX*wwww)) : -((double)rand() / (RAND_MAX * wwww)));
			}
		}
	}

	// �������� ����� �������� ������� ����
	vector<Filter<double>> FILTERS1(f2_count);
	for (int i = 0; i < f2_count; i++) {
		FILTERS1[i] = Filter<double>(filter1_height, filter1_width);
		for (int j = 0; j < FILTERS1[i].getN(); j++) {
			for (int p = 0; p < FILTERS1[i].getM(); p++) {
				FILTERS1[i][j][p] = (p % 2 ? ((double)rand() / (RAND_MAX * wwww)) : -((double)rand() / (RAND_MAX * wwww)));
			}
		}
	}

	// �������� ����� �������� ���� �����������
	Matrix<Weights<double>> WEIGHTS(1, w1_count);
	for (int i = 0; i < w1_count; i++) {
		WEIGHTS[0][i] = Weights<double>(neyron_height, neyron_width);
		for (int j = 0; j < WEIGHTS[0][i].getN(); j++) {
			for (int p = 0; p < WEIGHTS[0][i].getM(); p++) {
				WEIGHTS[0][i][j][p] = (p % 2 ? ((double)rand() / (RAND_MAX * wwww)) : -((double)rand() / (RAND_MAX * wwww)));
			}
		}
		WEIGHTS[0][i].GetWBias() = (i % 2 ? ((double)rand() / (RAND_MAX * wwww)) : -((double)rand() / (RAND_MAX * wwww)));
	}
	// �������� ����� ��� ������� ���� �����������
	Matrix<Weights<double>> WEIGHTS1(1, w2_count);
	for (int i = 0; i < w2_count; i++) {
		WEIGHTS1[0][i] = Weights<double>(neyron1_height, neyron1_width);
		for (int j = 0; j < WEIGHTS1[0][i].getN(); j++) {
			for (int p = 0; p < WEIGHTS1[0][i].getM(); p++) {
				WEIGHTS1[0][i][j][p] = (p % 2 ? ((double)rand() / (RAND_MAX * wwww)) : -((double)rand() / (RAND_MAX * wwww)));
			}
		}
		WEIGHTS1[0][i].GetWBias() = (i % 2 ? ((double)rand() / (RAND_MAX * wwww)) : -((double)rand() / (RAND_MAX * wwww)));
	}

	// ������� ������ ����
	Matrix<double> MATRIX_OUT(1, w1_count);
	
	// ������� ������ �����������
	Matrix<double> IMAGE_OUT(neyron_height, neyron_width);

	double summ; // ���������� �����
	double y[w2_count]; // ���������� ������ ����

	// ������� �����������
	Matrix<double> IMAGE_1(image_height, image_width);
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
		IMAGE_4[i] = Matrix<double>(8, 8);
	}

	vector< Matrix<double>> IMAGE_5(f2_count);
	for (int i = 0; i < f2_count; i++) {
		IMAGE_5[i] = Matrix<double>(4, 4);
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
		IMAGE_4_D[i] = Matrix<double>(8, 8);
	}

	vector< Matrix<double>> IMAGE_5_D(f2_count);
	for (int i = 0; i < f2_count; i++) {
		IMAGE_5_D[i] = Matrix<double>(4, 4);
	}
	// ������� ������ ������ �����������
	Matrix<double> IMAGE_OUT_D(neyron_height, neyron_width);
	IMAGE_OUT.Fill(0);

	// ������������������ ����, �������� ��� ��������� ����������� ������������
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

	long int koll = 100; // ���������� �������� ���������

	// �������� ��������� �������
	vector<vector<Matrix<double>>> Nums(10);
	for (int i = 0; i < 10; i++) {
		Nums[i] = vector<Matrix<double>>(koll);
	}

	//���������� �����
	//ifstream fWeightss;
	//fWeightss.open("Weights.txt");
	//for (int i = 0; i < f1_count; i++) {
	//	fWeightss >> FILTERS[i];
	//}
	//for (int i = 0; i < f2_count; i++) {
	//	fWeightss >> FILTERS1[i];
	//}
	//fWeightss >> WEIGHTS;
	//fWeightss >> WEIGHTS1;
	//fWeightss.close();

	// ������, ������ ��� �������� ������
	double a[10];

	// ���������� ��������� �������
	string folder = "..\\Image_to_txt\\";
	string file;
	string path;
	ifstream input;
	for (int i = 0; i < 10; i++) {
		file = to_string(i) + ".txt";
		path = folder + file;
		input.open(path);
		for (int j = 0; j < koll; j++) {
			input >> Nums[i][j];
		}
		input.close();
	}
	int max = 0;
	// �������� ����
	for (long int i = 0; i < koll; i++) {
		cout << i << endl;
		//Teacher.shuffle(nums, 10); // ��������� ������������������
		for (int j = 0; j < 10; j++) { // ���� ������� �� ��������� �������
			cout << "	a)" << j << endl;
			for (int u = 0; u < 2; u++) {
				cout << (NUMBER) << ": " << u << ") ";
				max = 0;
				// ������ ����
				// ���������� ������� �������� �� ���� ����
				IMAGE_1 = Nums[NUMBER][(i%2) == 0 ? i:i-i%2];
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
				for (int l = 0; l < f2_count; l++) {
					for (int li = 0; li < 4; li++) {
						for (int lj = 0; lj < 4; lj++) {
							IMAGE_OUT[li][l * 4 + lj] = IMAGE_5[l][li][lj];
						}
					}
				}
				// ������ �� �����������
				// ������ �� ������� ����
				for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
					summ = Neyron.Summator(IMAGE_OUT, WEIGHTS[0][l]); // ��������� ���������� �����
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
				cout << max << ' ';
				// ������ ������
				for (int i = 0; i < w2_count; i++) {
					if (i == NUMBER)
						a[i] = 1;
					if (i != NUMBER)
						a[i] = 0;
				}
				// ����� ������ �� �����
				cout << Teacher.RMS_error(a, y, w2_count) << endl;
				// ���� ������ ����, ���������� ���� ��������, ��� �� �������� ������������ ����
				if (Teacher.RMS_error(a, y, w2_count) < 0.2) {
					continue;
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
				// ��������������� ������ �� ������� ���� �����������
				for (int l = 0; l < w2_count; l++) {
					Teacher.BackPropagation(WEIGHTS, WEIGHTS1[0][l]);
				}
				// ��������������� ������ �� ����� ��������
				for (int l = 0; l < w2_count; l++) {
					TeacherCNN.Revers_Perceptron_to_CNN(IMAGE_OUT_D, WEIGHTS[0][l]);
				}
				// ����������� ������ �� ������������� ����
				for (int l = 0; l < f2_count; l++) {
					for (int li = 0; li < 4; li++) {
						for (int lj = 0; lj < 4; lj++) {
							IMAGE_5_D[l][li][lj] = IMAGE_OUT_D[li][l * 4 + lj];
						}
					}
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
					Teacher.GradDes(WEIGHTS[0][l], IMAGE_OUT, f, MATRIX_OUT[0][l]);
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
				IMAGE_OUT_D.Fill(0);
				Teacher.getE() -= Teacher.getE() * 0.00001;
				TeacherCNN.getE() -= TeacherCNN.getE() * 0.00001;
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
			for (int l = 0; l < f2_count; l++) {
				for (int li = 0; li < 4; li++) {
					for (int lj = 0; lj < 4; lj++) {
						IMAGE_OUT[li][l * 4 + lj] = IMAGE_5[l][li][lj];
					}
				}
			}
			// ������ �� �����������
			// ������ �� ������� ����
			for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
				summ = Neyron.Summator(IMAGE_OUT, WEIGHTS[0][l]); // ��������� ���������� �����
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
	// ���������� �������� �������
	folder = "..\\Image_to_txt\\";
	for (int i = 0; i < 10; i++) {
		file = to_string(i) + "_tests.txt";
		path = folder + file;
		ifstream inputt(path);
		for (int j = 0; j < 10; j++) {
			inputt >> TestNums[i][j];
		}
		inputt.close();
	}

	// ����� �� ����� ���������� ������������ ����
	cout << "Test network:" << endl;
	for (int i = 0; i < 10; i++) { // ���� ������� �� �������� �������
		max = 0;
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
		for (int l = 0; l < f2_count; l++) {
			for (int li = 0; li < 4; li++) {
				for (int lj = 0; lj < 4; lj++) {
					IMAGE_OUT[li][l * 4 + lj] = IMAGE_5[l][li][lj];
				}
			}
		}
		// ������ �� �����������
		// ������ �� ������� ����
		for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
			summ = Neyron.Summator(IMAGE_OUT, WEIGHTS[0][l]); // ��������� ���������� �����
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