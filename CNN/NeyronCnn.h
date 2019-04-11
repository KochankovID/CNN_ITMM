#pragma once
#include "Matrix.h"
#include <string>
#include "Filter.h"

class Neyron�nn : public Matrix
{
public:
	// ������������ ----------------------------------------------------------
	Neyron�nn();
	Neyron�nn(const int& i_, const int& j_, const int& step_);
	Neyron�nn(int** arr_, const int& i_, const int& j_, const int& step_);
	Neyron�nn(const Neyron�nn& copy);

	// ������ ������ ---------------------------------------------------------
	void Padding(); // ���������� "�����" � �������
	// Pooling(); // �������� "�������"
	void Svertka(Filter& F); // �������� ������� ��� �������� ��������
	void SetStep(const int& step_) // ��������� ���� �������
	{
		if ((step_ < 0) || (step_ > n) || (step_ > m)) {
			throw Neyron�nnExeption("����� ����������� ��� �������!");
		}
		step = step_;
	}
	// ���������� ���������� -------------------------------------------------
	Neyron�nn& operator= (const Neyron�nn& copy);

	// ���������� ------------------------------------------------------------
	~Neyron�nn();

	// ����� ���������� ------------------------------------------------------
	class Neyron�nnExeption : std::runtime_error {
	public:
		Neyron�nnExeption(std::string str) : std::runtime_error(str) {};
		~Neyron�nnExeption() {};
	};
private:
	int step; // ��� �������
};
