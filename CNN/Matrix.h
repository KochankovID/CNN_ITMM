#pragma once
#include <string>
class Matrix

{
public:
	// ������������ ---------------------------------
	Matrix(); // ����������� �� ��������� -----------
	Matrix(int** arr, const int& i, const int& j); // ����������� �������������
	Matrix(const int& i, const int& j); // ����������� ������������� (������� ������� ��������� ������� ����������� 0)
	Matrix(const Matrix& copy); // ����������� ����������� 

	// ������ ������ --------------------------------
	int getN() const // ��������� ���������� �����
	{
		return n;
	}
	int getM() const // ��������� ����������� ��������
	{
		return m;
	}
	const int** asArray() const // ��������� ������� � ���� �������
	{
		return const_cast<const int**>(arr);
	}

	// ���������� ���������� ------------------------
	Matrix& operator= (const Matrix& copy); // �������� ������������
	Matrix operator+ (const Matrix& mat) const; // �������� �����
	Matrix operator* (const Matrix& mat) const; // �������� ������������
	Matrix operator* (const int k) const; // �������� ������������ �� �����
	friend Matrix operator* (const int k, const Matrix& mat); // �������� ������������ �� �����
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat); // �������� ����� ������� � �����
	friend std::istream& operator>>(std::istream& out, Matrix& mat); // �������� ������ ������� �� ������
	int* operator[] (int index); // �������� ����������
	const int* operator[] (int index) const; // �������� ���������� ���������
	bool operator==(const Matrix& mat) const; // �������� ��������� ������


	// ���������� -----------------------------------
	~Matrix();

	// ��������� ���������� ----------------------------
	struct MatrixExeption : std::runtime_error
	{
		MatrixExeption(std::string s) : std::runtime_error(s) {}
	};
private:

	// ���� ������ ----------------------------------
	int n, // ���������� ����� � �������
		m; // ���������� �������� � �������
	int** arr; // �������

	// ������� ������ ������ ------------------------
	void initMat(); // ��������� ������ ��� �������
	void isInRange(int index) const; // ���������, ��������� �� ������ � ���������� ��������
};
