#pragma once
#include "Matrix.h"
#include <string>
#include "Filter.h"

class NeyronСnn : public Matrix
{
public:
	// Конструкторы ----------------------------------------------------------
	NeyronСnn();
	NeyronСnn(const int& i_, const int& j_, const int& step_);
	NeyronСnn(int** arr_, const int& i_, const int& j_, const int& step_);
	NeyronСnn(const NeyronСnn& copy);

	// Методы класса ---------------------------------------------------------
	void Padding(); // Добавление "полей" к матрице
	// Pooling(); // Операция "пулинга"
	void Svertka(Filter& F); // Операция свертки над матрицей значений
	void SetStep(const int& step_) // Установка шага свертки
	{
		if ((step_ < 0) || (step_ > n) || (step_ > m)) {
			throw NeyronСnnExeption("Задан невозможный шаг свертки!");
		}
		step = step_;
	}
	// Перегрузка операторов -------------------------------------------------
	NeyronСnn& operator= (const NeyronСnn& copy);

	// Деструктор ------------------------------------------------------------
	~NeyronСnn();

	// Класс исключения ------------------------------------------------------
	class NeyronСnnExeption : std::runtime_error {
	public:
		NeyronСnnExeption(std::string str) : std::runtime_error(str) {};
		~NeyronСnnExeption() {};
	};
private:
	int step; // Шаг свертки
};
