#pragma once
#include "Base_Perceptron.h"

template <typename T, typename Y>
class NeyronPerceptron : public Base_Perceptron<T, Y>
{
public:
	// ������������ ----------------------------------------------------------
	NeyronPerceptron();
	NeyronPerceptron(const NeyronPerceptron& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	// ������� ��������� �������
	Y FunkActiv(const T& e, Func<T,Y>& f);

	// ���������� ���������� -------------------------------------------------
	NeyronPerceptron& operator= (const NeyronPerceptron& copy) = delete; // ������ �����������
	
	// ���������� ------------------------------------------------------------
	~NeyronPerceptron();
};

template <typename T, typename Y>
NeyronPerceptron<T,Y>::NeyronPerceptron() : Base_Perceptron<T,Y>()
{
}

template<typename T, typename Y>
inline Y NeyronPerceptron<T, Y>::FunkActiv(const T & e, ::Func<T,Y>& f)
{
	return f(e);
}

template <typename T, typename Y>
NeyronPerceptron<T, Y>::~NeyronPerceptron()
{
}



