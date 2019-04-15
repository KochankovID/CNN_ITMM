#pragma once
#include "Base_Perceptron.h"
#include "Func.h"

template <typename T, typename Y>
class NeyronPerceptron : Base_Perceptron<T, Y>
{
public:
	// Конструкторы ----------------------------------------------------------
	NeyronPerceptron();
	NeyronPerceptron(const NeyronPerceptron& copy) = delete; // Запрет копирования

	// Методы класса ---------------------------------------------------------
	// Функция активации нейрона
	Y FunkActiv(const T& e, Func<Y> f);

	// Перегрузка операторов -------------------------------------------------
	NeyronPerceptron& operator= (const NeyronPerceptron& copy) = delete; // Запрет копирования
	friend std::ostream& operator<<(std::ostream& out, const NeyronPerceptron& mat) = delete; // Запрет вывода в поток
	friend std::istream& operator>>(std::istream& out, NeyronPerceptron& mat) = delete; // Запрет считывания из потока

	// Деструктор ------------------------------------------------------------
	~NeyronPerceptron();

	// Класс исключения ------------------------------------------------------
	class NeyronPerceptronExeption : public std::runtime_error {
	public:
		NeyronPerceptronExeption(std::string str) : std::runtime_error(str) {};
		~NeyronPerceptronExeption() {};
	};
};

template <typename T, typename Y>
NeyronPerceptron<T,Y>::NeyronPerceptron() : Base_Perceptron()
{
}

template<typename T, typename Y>
inline Y NeyronPerceptron<T, Y>::FunkActiv(const T & e, Func<Y> f)
{
	return Y();
}

template <typename T, typename Y>
NeyronPerceptron<T, Y>::~NeyronPerceptron()
{
}



