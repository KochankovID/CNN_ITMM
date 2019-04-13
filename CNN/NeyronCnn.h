#pragma once
#include "Matrix.h"
#include <string>
#include "Filter.h"

class NeyronСnn : public Matrix
{
public:
	// Конструкторы ----------------------------------------------------------
	NeyronСnn();
	NeyronСnn(const int& i_, const int& j_, const int& step_ = 1);
	NeyronСnn(double** arr_, const int& i_, const int& j_, const int& step_ = 1);
	NeyronСnn(const NeyronСnn& copy);

	// Методы класса ---------------------------------------------------------
	 // Добавление "полей" к матрице
	void Padding();

	// Операция "Макс пулинга"
	void Pooling(const int& n_, const int& m_);

	 // Операция свертки над матрицей значений
	void Svertka(Filter& F);

	// Получение шага свертки
	int GetStep() const { return step; }

	// Установка шага свертки
	void SetStep(const int& step_)
	{
		if ((step_ < 0) || (step_ > n) || (step_ > m)) {
			throw NeyronСnnExeption("Задан невозможный шаг свертки!");
		}
		step = step_;
	}

	// Перегрузка операторов -------------------------------------------------
	NeyronСnn& operator= (const NeyronСnn& copy); // Перегрузка оператора присваивания
	friend std::ostream& operator<<(std::ostream& out, const NeyronСnn& mat); // Оператор вывод матрицы в поток
	friend std::istream& operator>>(std::istream& out, NeyronСnn& mat); // Оператор чтение матрицы из потока

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
