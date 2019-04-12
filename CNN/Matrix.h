#pragma once
#include <string>
class Matrix

{
public:
	// ������������ ---------------------------------
	Matrix(); // ����������� �� ��������� -----------
	Matrix(double** arr_, const int& i, const int& j); // ����������� �������������
	Matrix(const int& i, const int& j); // ����������� ������������� (������� ������� ��������� ������� ����������� 0)
	Matrix(const Matrix& copy); // ����������� ����������� 

	// ������ ������ --------------------------------
	// ��������� ���������� �����
	int getN() const
	{
		return n;
	}

	// ��������� ����������� ��������
	int getM() const
	{
		return m;
	}

	// ����� ��������� � �������
	static double Max(double** arr_, const int& n_, const int& m_);

	// ��������� ������� � ���� �������
	const double** asArray() const
	{
		return const_cast<const double**>(arr);
	}

	// ��������� ����� ������� � ���� �������
	double** getCopy();

	// ��������� ����������
	double** getPodmatrix(const int& poz_n_, const int& poz_m_, const int& n_, const int& m_);

	// ���������� ���������� ------------------------
	Matrix& operator= (const Matrix& copy); // �������� ������������
	Matrix operator+ (const Matrix& mat) const; // �������� �����
	Matrix operator* (const Matrix& mat) const; // �������� ������������
	Matrix operator* (const int k) const; // �������� ������������ �� �����
	friend Matrix operator* (const int k, const Matrix& mat); // �������� ������������ �� �����
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat); // �������� ����� ������� � �����
	friend std::istream& operator>>(std::istream& out, Matrix& mat); // �������� ������ ������� �� ������
	double* operator[] (int index); // �������� ����������
	const double* operator[] (int index) const; // �������� ���������� ���������
	bool operator==(const Matrix& mat) const; // �������� ��������� ������


	// ���������� -----------------------------------
	~Matrix();

	// ����� ���������� ----------------------------
	class MatrixExeption : public std::runtime_error
	{
	public:
		MatrixExeption(std::string s) : std::runtime_error(s) {}
		~MatrixExeption() {}
	};
protected:

	// ���� ������ ----------------------------------
	int n, // ���������� ����� � �������
		m; // ���������� �������� � �������
	double** arr; // �������

	// ������� ������ ������ ------------------------
	void initMat(); // ��������� ������ ��� �������
	void isInRange(int index) const; // ���������, ��������� �� ������ � ���������� ��������
};
