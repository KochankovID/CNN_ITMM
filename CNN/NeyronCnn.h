#pragma once
#include "Matrix.h"
#include <string>
#include "Filter.h"

class NeyronСnn
{
public:
	// Конструкторы ----------------------------------------------------------
	NeyronСnn();
	explicit NeyronСnn(const int& step_ );
	NeyronСnn(const NeyronСnn& copy) = delete; // Запрет копирования

	// Методы класса ---------------------------------------------------------
	 // Добавление "полей" к матрице
	void Padding(Matrix& a);

	// Операция "Макс пулинга"
	void Pooling(Matrix& a, const int& n_, const int& m_);

	 // Операция свертки над матрицей значений
	void Svertka(const Filter& F, Matrix& a);

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
	NeyronСnn& operator= (const NeyronСnn& copy) = delete; // Запрет копирования
	friend std::ostream& operator<<(std::ostream& out, const NeyronСnn& mat) = delete; // Запрет вывода в поток
	friend std::istream& operator>>(std::istream& out, NeyronСnn& mat) = delete; // Запрет считывания из потока

	// Деструктор ------------------------------------------------------------
	~NeyronСnn();

	// Класс исключения ------------------------------------------------------
	class NeyronСnnExeption : public std::runtime_error {
	public:
		NeyronСnnExeption(std::string str) : std::runtime_error(str) {};
		~NeyronСnnExeption() {};
	};
private:
	int step; // Шаг свертки
};
