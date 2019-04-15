#pragma once
#include "Base_Perceptron.h"
#include "Func.h"

template <typename T, typename Y>
class NeyronPerceptron : public Base_Perceptron<T, Y>
{
public:
	// ������������ ----------------------------------------------------------
	NeyronPerceptron();
	NeyronPerceptron(const NeyronPerceptron& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	// ������� ��������� �������
	Y FunkActiv(const T& e, Func<Y> f);

	// ���������� ���������� -------------------------------------------------
	NeyronPerceptron& operator= (const NeyronPerceptron& copy) = delete; // ������ �����������
	
	// ���������� ------------------------------------------------------------
	~NeyronPerceptron();

	// ����� ���������� ------------------------------------------------------
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



