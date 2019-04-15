#pragma once
#include <string>

template <typename T>
class Matrix
{
public:
	// ������������ ---------------------------------
	Matrix(); // ����������� �� ��������� -----------
	Matrix(T** arr_, const int& i, const int& j); // ����������� �������������
	Matrix(const int& i, const int& j); // ����������� ������������� (������� ������� ��������� ������� ����������� 0)
	Matrix(const Matrix<T>& copy); // ����������� ����������� 

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

	// ����� ��������� � ������� ���� �� ����
	static T Max(T** arr_, const int& n_, const int& m_);

	// ����� ��������� � �������
	T Max();

	// ��������� ����� ������� � ���� �������
	T** getCopy();

	// ��������� ����������
	Matrix<T> getPodmatrix(const int& poz_n_, const int& poz_m_, const int& n_, const int& m_);

	// ���������� ���������� ------------------------
	Matrix<T>& operator= (const Matrix<T>& copy); // �������� ������������
	Matrix<T> operator+ (const Matrix<T>& mat) const; // �������� �����
	Matrix<T> operator* (const Matrix<T>& mat) const; // �������� ������������
	Matrix<T> operator* (const int k) const; // �������� ������������ �� �����
	template <typename T1> friend Matrix<T1> operator* (const int k, const Matrix<T1>& mat); // �������� ������������ �� �����
	template <typename T1> friend std::ostream& operator<< (std::ostream& out, const Matrix<T1>& mat); // �������� ����� ������� � �����
	template <typename T1> friend std::istream& operator>> (std::istream& out, Matrix<T1>& mat); // �������� ������ ������� �� ������
	std::shared_ptr<T[]> operator[] (int index); // �������� ����������
	const std::shared_ptr<T[]> operator[] (int index) const; // �������� ���������� ���������
	bool operator==(const Matrix<T>& mat) const; // �������� ��������� ������


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
	std::shared_ptr < std::shared_ptr<T []>[] > arr; // �������

	// ������� ������ ������ ------------------------
	void initMat(); // ��������� ������ ��� �������
	void isInRange(int index) const; // ���������, ��������� �� ������ � ���������� ��������
};


// ���������� ---------------------------------------
template<typename T>
Matrix<T>::Matrix() : n(0), m(0)
{
	arr = nullptr;
}

template<typename T>
Matrix<T>::Matrix(T** arr_, const int& i, const int& j) : n(i), m(j)
{
	if ((n < 0) || (m < 0)) {
		throw Matrix::MatrixExeption("�������� ������ �������!");
	}
	initMat();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = arr_[i][j];
		}
	}
}

template<typename T>
Matrix<T>::Matrix(const int& i, const int& j) : n(i), m(j)
{
	if ((n < 0) || (m < 0)) {
		throw Matrix::MatrixExeption("�������� ������ �������!");
	}
	initMat();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = 0;
		}
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & copy) : n(copy.n), m(copy.m)
{
	initMat();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = copy.arr[i][j];
		}
	}
}

template<typename T>
Matrix<T> Matrix<T>::getPodmatrix(const int& poz_n_, const int& poz_m_, const int& n_, const int& m_) {
	if ((poz_n_ < 0) || (poz_m_ < 0)||(poz_n_ >= n)||(poz_m_ >= m)) {
		throw Matrix::MatrixExeption("�������� ������� �������� ������ �������� ����������!");
	}
	if (((poz_n_ + n_) > n) || ((poz_m_ + m_) > m)) {
		throw Matrix::MatrixExeption("���������� ������� �� ������� �������!");
	}

	Matrix<T> rez(n_, m_);

	for (int i = 0; i < n_; i++) {
		for (int j = 0; j < m_; j++) {
			rez[i][j] = arr[poz_n_ + i][poz_m_ + j];
		}
	}
	return rez;
}

template<typename T>
T Matrix<T>::Max(T** arr_, const int& n_, const int& m_) {
	T max = arr_[0][0];
	for (int i = 0; i < n_; i++) {
		for (int j = 0; j < m_; j++) {
			if (arr_[i][j] > max) {
				max = arr_[i][j];
			}
		}
	}
	return max;
}

template<typename T>
T Matrix<T>::Max() {
	T max = arr[0][0];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
			}
		}
	}
	return max;
}

template<typename T>
T** Matrix<T>::getCopy()
{
	T** copy;
	copy = new T*[n];
	for (int i = 0; i < n; i++) {
		copy[i] = new T[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			copy[i][j] = arr[i][j];
		}
	}
	return copy;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> & copy)
{
	if (this == &copy) {
		return *this;
	}
	if ((copy.n > n) || (copy.m > m)) {
		for (int i = 0; i < n; i++) {
			arr[i].reset();
		}
		arr.reset();
		n = copy.n;
		m = copy.m;
		initMat();
	}
	else {
		n = copy.n;
		m = copy.m;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = copy.arr[i][j];
		}
	}
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & mat) const
{
	Matrix<T> tmp(*this);
	if ((n != mat.n) || (m != mat.m)) {
		throw MatrixExeption("���������� ��������� �������� ������ ������� �������");
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[i][j] += mat.arr[i][j];
		}
	}
	return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & mat) const
{
	if (m != mat.n) {
		throw MatrixExeption("���������� ��������� ��������� ������ � ������������� ����������� �������� � ������ � ����� �� ������");
	}
	Matrix<T> tmp(n, mat.m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < mat.m; j++) {
			for (int o = 0; o < m; o++) {
				tmp[i][j] += (arr[i][o] * mat.arr[o][j]);
			}
		}
	}
	return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const int k) const
{
	Matrix<T> tmp(*this);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[i][j] *= k;
		}
	}
	return tmp;
}

template<typename T>
std::shared_ptr<T[]> Matrix<T>::operator[](int index)
{
	isInRange(index);
	return arr[index];
}

template<typename T>
const std::shared_ptr<T[]> Matrix<T>::operator[](int index) const
{
	isInRange(index);
	return arr[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & mat) const
{
	if ((n != mat.n) || (m != mat.m)) {
		return false;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] != mat.arr[i][j]) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < n; i++) {
		arr[i].reset();
		arr[i] = nullptr;
	}
	arr.reset();
	arr = nullptr;
}

template<typename T>
void Matrix<T>::initMat()
{
	arr.reset(new std::shared_ptr<T []>[n]);
	for (int i = 0; i < n; i++) {
		arr[i].reset(new T[m]);
	}
}

template<typename T>
void Matrix<T>::isInRange(int index) const
{
	if ((index > n) || (index < 0)) {
		throw MatrixExeption("������ ������� �� ������ �������!");
	}
}

template<typename T>
Matrix<T> operator*(const int k, const Matrix<T> & mat)
{
	Matrix<T> tmp(mat);
	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < mat.m; j++) {
			tmp[i][j] *= k;
		}
	}
	return tmp;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T> & mat)
{
	out << mat.n << ' ' << mat.m << std::endl; // ��� ������������� � ������ �� �����

	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < mat.m; j++) {
			out << mat.arr[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}

template<typename T>
std::istream& operator>>(std::istream & in, Matrix<T> & mat)
{
	in >> mat.n;
	in >> mat.m;
	if ((mat.n < 0) || (mat.m < 0)) {
		throw Matrix<T>::MatrixExeption("�������� ������ �������!");
	}
	mat.initMat();
	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < mat.m; j++) {
			in >> mat.arr[i][j];
		}
	}
	return in;
}