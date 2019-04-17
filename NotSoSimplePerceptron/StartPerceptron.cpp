//: Нейросеть распознающая все цифры

#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>
#define Teach

// функтор
class Sign : public DD_Func
{
public:
	Sign() : DD_Func() {};
	double operator()(const double& x) {
		if (x <= 0) {
			return -1;
		}
		else {
			return 1;
		}
	}
	~Sign() {};
};

using namespace std;
int main()
{
	// Создание перцептрона
	DD_Perceptron Neyron;

	// Создание обучателя сети
	DD_Leaning Teacher;
	/*for(int i = 0 ; i < 7; i++)
		Teacher.getE() -= 0.1;*/
	Teacher.getE() = 1;

	// Создание функтора
	Sign F;

	vector<Weights<double>> W(10);
	for (int i = 0; i < 10; i++) {
		W[i] = Weights<double>(5, 3);
	}

	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };
#ifdef Teach

	// Создание обучающей выборки
	double Zero[15] = { 1, 1, 1,
					    1, 0, 1,
					    1, 0, 1,
					    1, 0, 1,
					    1, 1, 1 };

	double One[15] = {  0, 0, 1,
					    0, 0, 1,
					    0, 0, 1,
					    0, 0, 1,
					    0, 0, 1 };

	double Two[15] = { 1, 1, 1,
					   0, 0, 1,
					   1, 1, 1,
					   1, 0, 0,
					   1, 1, 1 };

	double Three[15] = { 1, 1, 1,
					     0, 0, 1,
					     1, 1, 1,
					     0, 0, 1,
					     1, 1, 1 };

	double Four[15] = { 1, 0, 1,
					    1, 0, 1,
					    1, 1, 1,
					    0, 0, 1,
					    0, 0, 1 };

	double Five[15] = { 1, 1, 1,
					    1, 0, 0,
					    1, 1, 1,
					    0, 0, 1,
					    1, 1, 1 };

	double Six[15] = { 1, 1, 1,
					   1, 0, 0,
					   1, 1, 1,
					   1, 0, 1,
					   1, 1, 1 };

	double Seven[15] = { 1, 1, 1,
					     0, 0, 1,
					     0, 0, 1,
					     0, 0, 1,
					     0, 0, 1 };

	double Eight[15] = { 1, 1, 1,
					     1, 0, 1,
					     1, 1, 1,
					     1, 0, 1,
					     1, 1, 1 };

	double Nine[15] = { 1, 1, 1,
					    1, 0, 1,
					    1, 1, 1,
					    0, 0, 1,
					    1, 1, 1 };

	vector<Matrix<double>> Nums(10);
	Nums[0] = Matrix<double>(Zero, 5, 3);
	Nums[1] = Matrix<double>(One, 5, 3);
	Nums[2] = Matrix<double>(Two, 5, 3);
	Nums[3] = Matrix<double>(Three, 5, 3);
	Nums[4] = Matrix<double>(Four, 5, 3);
	Nums[5] = Matrix<double>(Five, 5, 3);
	Nums[6] = Matrix<double>(Six, 5, 3);
	Nums[7] = Matrix<double>(Seven, 5, 3);
	Nums[8] = Matrix<double>(Eight, 5, 3);
	Nums[9] = Matrix<double>(Nine, 5, 3);

	// Обучение сети


	long int k = 167;
	double summ; // Переменная суммы
	double y; // Переменная выхода сети
	// Создание весов нейрона

	for (long int i = 0; i < k; i++) {
		for (int j = 0; j < 10; j++) {
			for (int l = 0; l < 10; l++) {
				Teacher.shuffle(nums, 10);
				summ = Neyron.Summator(Nums[nums[j]], W[l]);
				y = Neyron.FunkActiv(summ, F);
				if (nums[j] != l) {
					Teacher.WTSimplePerceptron(-1, y, W[l], Nums[nums[j]]);
				}
				else {
					Teacher.WTSimplePerceptron(1, y, W[l], Nums[nums[j]]);
				}
			}
		}
	}

		// Сохраняем веса
		ofstream file;
		file.open("Weights.txt");
		for (int i = 0; i < 10; i++) {
			file << W[i];
		}
		file.close();

#else
	// Считывание весов
	ifstream file;
	file.open("Weights.txt");
	for (int i = 0; i < 10; i++) {
		file >> W[i];
	}
	file.close();
#endif // Teach

	// Создание тестовой выборки
	double Zero_zero[15] = { 0, 1, 1,
							 1, 0, 1,
							 1, 0, 1,
							 1, 0, 1,
							 1, 0, 1 };

	double One_one[15] = { 0, 0, 1,
						   0, 0, 1,
						   0, 0, 0,
						   0, 0, 1,
						   0, 0, 1 };

	double  Two_two[15] = { 1, 0, 1,
							0, 0, 1,
							1, 1, 1,
							1, 0, 0,
							1, 1, 1 };

	double Three_three[15] = { 0, 1, 1,
							   0, 0, 1,
							   1, 1, 1,
							   0, 0, 1,
							   1, 0, 1 };

	double Four_four[15] = { 1, 0, 1,
							 0, 0, 1,
							 1, 1, 0,
							 0, 0, 1,
							 0, 0, 1 };

	double Five_five[15] = { 1, 1, 1,
							 1, 0, 0,
							 1, 0, 1,
							 0, 0, 1,
							 0, 1, 1 };

	double Six_six[15] = { 1, 1, 1,
						   1, 0, 0,
						   1, 1, 1,
						   1, 0, 1,
						   1, 0, 1 };

	double Seven_seven[15] = { 1, 0, 1,
							   0, 0, 0,
							   0, 0, 1,
							   0, 0, 1,
							   0, 0, 1 };

	double Eight_eight[15] = { 1, 0, 1,
							   1, 0, 1,
							   1, 1, 1,
							   1, 0, 1,
							   1, 0, 1 };

	double Nine_nine[15] = { 0, 1, 1,
							 1, 0, 1,
							 1, 1, 1,
							 0, 0, 1,
							 1, 1, 1 };

	vector<Matrix<double>> Tests(10);
	Tests[0] = Matrix<double>(Zero_zero, 5, 3);
	Tests[1] = Matrix<double>(One_one, 5, 3);
	Tests[2] = Matrix<double>(Two_two, 5, 3);
	Tests[3] = Matrix<double>(Three_three, 5, 3);
	Tests[4] = Matrix<double>(Four_four, 5, 3);
	Tests[5] = Matrix<double>(Five_five, 5, 3);
	Tests[6] = Matrix<double>(Six_six, 5, 3);
	Tests[7] = Matrix<double>(Seven_seven, 5, 3);
	Tests[8] = Matrix<double>(Eight_eight, 5, 3);
	Tests[9] = Matrix<double>(Nine_nine, 5, 3);


	cout << "Test network:" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Neyron.FunkActiv(Neyron.Summator(Tests[i], W[j]), F) == 1)
				cout << "Test " << i << " : " << "recognized " << j << endl;
		}
	}

	cout << endl << "Weights of network: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W[i].Out();
		cout << endl;
	}
	system("pause");
	return 0;

}

// отношение числа проходов к кофиценту скорости обучения равно 166,6666666666666
