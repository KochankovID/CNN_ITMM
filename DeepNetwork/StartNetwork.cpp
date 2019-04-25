//: Нейросеть распознающая все цифры

#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

// Макрос режима работы программы (с обучением или без)
#define Teach
#define OUT (X) std::cout << X;
#define NUMBER nums[j]

// функтор
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
	// Создание перцептрона
	DD_Perceptron Neyron;

	// Создание обучателя сети
	DD_Leaning Teacher;
	Teacher.getE() = 0.8;

	// Создание функтора
	Sigm F(4);
	SigmD f(4);
	srand(time(0));
	// Создание весов нейросети
	Matrix<Weights<double>> W(1,10);
	for (int i = 0; i < 10; i++) {
		W[0][i] = Weights<double>(5, 3);
		for (int j = 0; j < W[0][i].getN(); j++) {
			for (int p = 0; p < W[0][i].getM(); p++) {
				W[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// Создания весов для второго слоя сети
	Matrix<Weights<double>> W1(1, 10);
	for (int i = 0; i < 10; i++) {
		W1[0][i] = Weights<double>(1, 10);
		for (int j = 0; j < W1[0][i].getN(); j++) {
			for (int p = 0; p < W1[0][i].getM(); p++) {
				W1[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}
	//cout << W;
	//cout << W1;
#ifdef Teach

	// Последовательность цифр, тасуемая для получения равномерной рандомизации
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

	// Создание обучающей выборки
	vector<Matrix<double>> Nums(10);

	// Массив выходов первого слоя сети
	Matrix<double> m(1,10);

	// Считываем матрицы обучающей выборки
	ifstream TeachChoose;
	TeachChoose.open("TeachChoose.txt");
	for (int i = 0; i < Nums.size(); i++) {
		TeachChoose >> Nums[i];
	}
	TeachChoose.close();

	// Обучение сети
	long int k = 500; // Количество обучений нейросети
	double summ; // Переменная суммы
	double y[10]; // Переменная выхода сети

	for (long int i = 0; i < k; i++) {
		Teacher.shuffle(nums, 10); // Тасование последовательности
		cout << i << endl;
		for (int j = 0; j < 10; j++) { // Цикл прохода по обучающей выборке
			for (int u = 0; u < 5; u++) {
				for (int l = 0; l < 10; l++) { // Цикл прохода по сети
					summ = Neyron.Summator(Nums[NUMBER], W[0][l]); // Получение взвешенной суммы
					m[0][l] = Neyron.FunkActiv(summ, F);
				}
				for (int l = 0; l < 10; l++) { // Цикл прохода по сети
					summ = Neyron.Summator(m, W1[0][l]); // Получение взвешенной суммы
					y[l] = Neyron.FunkActiv(summ, F); // Запись выхода l-того нейрона в массив выходов сети
				}
				for (int l = 0; l < 10; l++) { // Расчет ошибки для выходного слоя
					if (l == NUMBER) { // Если номер нейрона совпадает с поданной на вход цифрой, то ожидаеммый ответ 1
						W1[0][l].GetD() = Teacher.PartDOutLay(1, y[l]); // Расчет ошибки
					}
					else {// Если номер нейрона совпадает с поданной на вход цифрой, то ожидаеммый ответ 1
						W1[0][l].GetD() = Teacher.PartDOutLay(0, y[l]); // Расчет ошибки
					}
				}

				for (int l = 0; l < 10; l++) { // Распространение ошибки на скрытые слои нейросети
					Teacher.BackPropagation(W, W1[0][l]);
				}
				for (int l = 0; l < 10; l++) { // Примемение градиентного спуска по всем нейроннам первого слоя
					Teacher.GradDes(W[0][l], Nums[NUMBER], f, m[0][l]);
				}
				for (int l = 0; l < 10; l++) { // Примемение градиентного спуска по всем нейроннам второго слоя
					summ = Neyron.Summator(m, W1[0][l]);
					Teacher.GradDes(W1[0][l], m, f, summ);
				}
				for (int l = 0; l < 10; l++) { // Обнуление ошибки нейронов 1 слоя
					W[0][l].GetD() = 0;
				}
				Teacher.retract(W, 3);
				Teacher.retract(W1, 3);
			}
		}
	}

	// Сохраняем веса
	ofstream fWeights;
	fWeights.open("Weights.txt");
	fWeights << W;
	fWeights << W1;
	fWeights.close();

#else
	// Считывание весов
	ifstream fWeights;
	fWeights.open("Weights.txt");
	fWeights >> W;
	fWeights >> W1;
	fWeights.close();
#endif // Teach

	// Создание тестовой выборки
	vector<Matrix<double>> Tests(15);

	// Считывание тестовой выборки из файла
	ifstream Testsnums;
	Testsnums.open("Tests.txt");
	for (int i = 0; i < 14; i++) {
		Testsnums >> Tests[i];
	}

	// Вывод на экран реультатов тестирования сети
	cout << "Test network:" << endl;
	for (int j = 0; j < 14; j++) { // Цикл прохода по тестовой выборке
		for (int l = 0; l < 10; l++) { // Цикл прохода по сети
			summ = Neyron.Summator(Tests[j], W[0][l]); // Получение взвешенной суммы
			m[0][l] = Neyron.FunkActiv(summ, F);
		}
		for (int l = 0; l < 10; l++) { // Цикл прохода по сети
			summ = Neyron.Summator(m, W1[0][l]); // Получение взвешенной суммы
			y[l] = Neyron.FunkActiv(summ, F); // Запись выхода l-того нейрона в массив выходов сети
		}
		for (int l = 0; l < 10; l++) { // Получение результатов сети
			if (y[l] >= 0.9) {
				cout << "Test " << j << " : " << "recognized " << l << ' ' << y << endl;
			}
		}
	}

	// Вывод весов сети
	cout << endl << "Weights of network. First layer: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W[0][i].Out();
		cout << endl;
	}
	cout << endl << "Weights of network. First layer: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W1[0][i].Out();
		cout << endl;
	}
	system("pause");
	return 0;

}