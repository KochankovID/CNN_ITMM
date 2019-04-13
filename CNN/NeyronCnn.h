#pragma once
#include "Matrix.h"
#include <string>
#include "Filter.h"

class Neyron�nn
{
public:
	// ������������ ----------------------------------------------------------
	Neyron�nn();
	explicit Neyron�nn(const int& step_ );
	Neyron�nn(const Neyron�nn& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	 // ���������� "�����" � �������
	void Padding(Matrix& a);

	// �������� "���� �������"
	void Pooling(Matrix& a, const int& n_, const int& m_);

	 // �������� ������� ��� �������� ��������
	void Svertka(const Filter& F, Matrix& a);

	// ��������� ���� �������
	int GetStep() const { return step; }

	// ��������� ���� �������
	void SetStep(const int& step_)
	{
		if (step_ < 0) {
			throw Neyron�nnExeption("����� ����������� ��� �������!");
		}
		step = step_;
	}

	// ���������� ���������� -------------------------------------------------
	Neyron�nn& operator= (const Neyron�nn& copy) = delete; // ������ �����������
	friend std::ostream& operator<<(std::ostream& out, const Neyron�nn& mat) = delete; // ������ ������ � �����
	friend std::istream& operator>>(std::istream& out, Neyron�nn& mat) = delete; // ������ ���������� �� ������

	// ���������� ------------------------------------------------------------
	~Neyron�nn();

	// ����� ���������� ------------------------------------------------------
	class Neyron�nnExeption : public std::runtime_error {
	public:
		Neyron�nnExeption(std::string str) : std::runtime_error(str) {};
		~Neyron�nnExeption() {};
	};
private:
	int step; // ��� �������
};
