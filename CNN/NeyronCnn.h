#pragma once
#include "Matrix.h"
#include <string>
#include "Filter.h"

class Neyron�nn : public Matrix
{
public:
	// ������������ ----------------------------------------------------------
	Neyron�nn();
	Neyron�nn(const int& i_, const int& j_, const int& step_ = 1);
	Neyron�nn(double** arr_, const int& i_, const int& j_, const int& step_ = 1);
	Neyron�nn(const Neyron�nn& copy);

	// ������ ������ ---------------------------------------------------------
	 // ���������� "�����" � �������
	void Padding();

	// �������� "���� �������"
	void Pooling(const int& n_, const int& m_);

	 // �������� ������� ��� �������� ��������
	void Svertka(Filter& F);

	// ��������� ���� �������
	int GetStep() const { return step; }

	// ��������� ���� �������
	void SetStep(const int& step_)
	{
		if ((step_ < 0) || (step_ > n) || (step_ > m)) {
			throw Neyron�nnExeption("����� ����������� ��� �������!");
		}
		step = step_;
	}

	// ���������� ���������� -------------------------------------------------
	Neyron�nn& operator= (const Neyron�nn& copy); // ���������� ��������� ������������
	friend std::ostream& operator<<(std::ostream& out, const Neyron�nn& mat); // �������� ����� ������� � �����
	friend std::istream& operator>>(std::istream& out, Neyron�nn& mat); // �������� ������ ������� �� ������

	// ���������� ------------------------------------------------------------
	~Neyron�nn();

	// ����� ���������� ------------------------------------------------------
	class Neyron�nnExeption : public std::runtime_error {
	public:
		Neyron�nnExeption(std::string str) : std::runtime_error(str) {};
		~Neyron�nnExeption() {};
	};
private:
	// ���� ������ -----------------------------------------------------------
	int step; // ��� �������
};
