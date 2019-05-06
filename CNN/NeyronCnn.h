#pragma once
#include "Base_Cnn.h"
#include <string>


template<typename T>
class NeyronСnn : public Base_Cnn<T>
{
public:
	// Конструкторы ----------------------------------------------------------
	NeyronСnn();
	explicit NeyronСnn(const int& step_ );
	NeyronСnn(const NeyronСnn<T>& copy) = delete; // Запрет копирования

	// Методы класса ---------------------------------------------------------
	 // Операция свертки над матрицей значений
	Matrix<T> Svertka(const Matrix<T>& F, const Matrix<T>& a);

	// Получение доступа к шагу свертки
	int& GetStep() { return step; }

	// Перегрузка операторов -------------------------------------------------
	NeyronСnn& operator= (const NeyronСnn<T>& copy) = delete; // Запрет копирования
	
	// Деструктор ------------------------------------------------------------
	~NeyronСnn();

	// Класс исключения ------------------------------------------------------
	class NeyronСnnExeption : public Base_Cnn<T>::Base_CnnExeption {
	public:
		NeyronСnnExeption(std::string str) : Base_Cnn<T>::Base_CnnExeption(str) {};
		~NeyronСnnExeption() {};
	};
private:
	// Поля класса -----------------------------------------------------------
	int step; // Шаг свертки
};


template<typename T>
NeyronСnn<T>::NeyronСnn() : Base_Cnn<T>(), step(1)
{
}

template<typename T>
NeyronСnn<T>::NeyronСnn(const int& step_) : Base_Cnn<T>(), step(step_)
{
}


template<typename T>
Matrix<T> NeyronСnn<T>::Svertka(const Matrix<T>& F, const Matrix<T>& a)
{

	if ((step > a.getN()) || (step > a.getM())||(step < 1)) {
		throw NeyronСnnExeption("Задан невозможный шаг свертки!");
	}

	Matrix<T> rez((a.getN() - F.getN()) / step + 1, (a.getM() - F.getM()) / step + 1);

	double sum;
	Matrix<T> fokus;
	for (int i = 0; i < rez.getN(); i++) {
		for (int j = 0; j < rez.getM(); j++) {
			sum = 0;
			fokus = a.getPodmatrix(i*step, j*step, F.getN(), F.getM());
			for (int ii = 0; ii < F.getN(); ii++) {
				for (int jj = 0; jj < F.getM(); jj++) {
					sum += fokus[ii][jj] * F[ii][jj];
				}
			}
			rez[i][j] = sum;
		}
	}
	return rez;
}


template<typename T>
NeyronСnn<T>::~NeyronСnn()
{
}
