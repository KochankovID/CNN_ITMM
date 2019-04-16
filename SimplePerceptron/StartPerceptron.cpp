//: Нейросеть распознающая 4

#include "Perceptrons.h"
#include <vector>
#include <iostream>

// функтор
class Sign : public II_Func
{
public:
	Sign() : II_Func(){};
	int operator()(const int& x) {
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
	II_Perceptron Neyron;

	// Создание обучателя сети
	II_Leaning Teacher;

	// Создание функтора
	Sign F;

	// Создание весов нейрона
	Weights<int> Weight(5,3);
	
	// Создание обучающей выборки
	int Zero[15] = { 1, 1, 1,
					 1, 0, 1,
					 1, 0, 1,
					 1, 0, 1,
					 1, 1, 1 };

	int One[15] = {  0, 0, 1,
					 0, 0, 1,
					 0, 0, 1,
					 0, 0, 1,
					 0, 0, 1 };

	int Two[15] = { 1, 1, 1,
					0, 0, 1,
					1, 1, 1,
					1, 0, 0,
					1, 1, 1 };

	int Three[15] = { 1, 1, 1,
				      0, 0, 1,
			      	  1, 1, 1,
				      0, 0, 1,
				      1, 1, 1 };

	int Four[15] = { 1, 0, 1,
				     1, 0, 1,
				     1, 1, 1,
				     0, 0, 1,
				     0, 0, 1 };

	int Five[15] = { 1, 1, 1,
				     1, 0, 0,
				     1, 1, 1,
				     0, 0, 1,
				     1, 1, 1 };

	int Six[15] = { 1, 1, 1,
				    1, 0, 0,
				    1, 1, 1,
				    1, 0, 1,
				    1, 1, 1 };

	int Seven[15] = { 1, 1, 1,
				      0, 0, 1,
				      0, 0, 1,
				      0, 0, 1,
				      0, 0, 1 };

	int Eight[15] = { 1, 1, 1,
				      1, 0, 1,
				      1, 1, 1,
				      1, 0, 1,
				      1, 1, 1 };

	int Nine[15] = { 1, 1, 1,
				     1, 0, 1,
				     1, 1, 1,
				     0, 0, 1,
				     1, 1, 1 };

	vector<Matrix<int>> Nums(10);
	Nums[0] = Matrix<int>(Zero, 5, 3);
	Nums[1] = Matrix<int>(One, 5, 3);
	Nums[2] = Matrix<int>(Two, 5, 3);
	Nums[3] = Matrix<int>(Three, 5, 3);
	Nums[4] = Matrix<int>(Four, 5, 3);
	Nums[5] = Matrix<int>(Five, 5, 3);
	Nums[6] = Matrix<int>(Six, 5, 3);
	Nums[7] = Matrix<int>(Seven, 5, 3);
	Nums[8] = Matrix<int>(Eight, 5, 3);
	Nums[9] = Matrix<int>(Nine, 5, 3);

	// Обучение сети

	long int k = 1000;
	for (long int i = 0; i < k; i++) {
		for (int j = 0; j < 10; j++) {
			if (j != 4) {
				Teacher.WTSimplePerceptron(-1, Neyron.FunkActiv(Neyron.Summator(Nums[j], Weight), F), Weight,Nums[j]);
			}
			else {
				Teacher.WTSimplePerceptron(1, Neyron.FunkActiv(Neyron.Summator(Nums[j], Weight), F), Weight, Nums[j]);
			}
		}
	}

	// Создание тестовой выборки
	int Four_one[15] = { 1, 0, 1,
				      1, 0, 1,
				      1, 1, 1,
				      0, 0, 1,
				      0, 0, 1 };

	int Four_two[15] = { 1, 0, 1,
					  0, 0, 1,
					  1, 1, 1,
					  0, 0, 1,
					  0, 0, 1 };

	int Four_three[15] = { 1, 0, 1,
				           1, 0, 0,
				           1, 1, 1,
				           0, 0, 0,
				           0, 0, 1 };

	int Four_four[15] = { 1, 0, 1,
					      0, 0, 1,
					      1, 1, 0,
					      0, 0, 1,
					      0, 0, 1 };

	int Four_five[15] = { 0, 0, 1,
					      1, 0, 0,
					      1, 1, 1,
					      0, 0, 0,
					      0, 0, 1 };

	vector<Matrix<int>> Tests(5);
	Tests[0] = Matrix<int>(Four_one, 5, 3);
	Tests[1] = Matrix<int>(Four_two, 5, 3);
	Tests[2] = Matrix<int>(Four_three, 5, 3);
	Tests[3] = Matrix<int>(Four_four, 5, 3);
	Tests[4] = Matrix<int>(Four_five, 5, 3);

	cout << "Test network:" << endl;
	for (int i = 0; i < 5; i++) {
		Neyron.FunkActiv(Neyron.Summator(Tests[i], Weight), F) == 1 ? cout << "Test " << i << " : " << "recognized 4" << endl : cout << "Test " << i << " : " << "doesn't recognized 4" << endl;
	}

	cout << "Weights of network: " << endl;
	Weight.Out();
	system("pause");
	return 0;
}
