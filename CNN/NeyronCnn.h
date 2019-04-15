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
	void Svertka(const Filter<T>& F, Matrix<T>& a);

	// Получение шага свертки
	int GetStep() const { return step; }

	// Установка шага свертки
	void SetStep(const int& step_)
	{
		if (step_ < 0) {
			throw NeyronСnnExeption("Задан невозможный шаг свертки!");
		}
		step = step_;
	}

	// Перегрузка операторов -------------------------------------------------
	NeyronСnn& operator= (const NeyronСnn<T>& copy) = delete; // Запрет копирования
	
	// Деструктор ------------------------------------------------------------
	~NeyronСnn();

	// Класс исключения ------------------------------------------------------
	class NeyronСnnExeption : public std::runtime_error {
	public:
		NeyronСnnExeption(std::string str) : std::runtime_error(str) {};
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
void NeyronСnn<T>::Svertka(const Filter<T>& F, Matrix<T>& a)
{

	if ((step > a.getN()) || (step > a.getM())) {
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
	a = rez;
}


template<typename T>
NeyronСnn<T>::~NeyronСnn()
{
}
