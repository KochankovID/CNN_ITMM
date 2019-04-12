#pragma once
#include <string>
class Matrix

{
public:
	// Конструкторы ---------------------------------
	Matrix(); // Конструктор по умолчанию -----------
	Matrix(double** arr_, const int& i, const int& j); // Конструктор инициализатор
	Matrix(const int& i, const int& j); // Конструктор инициализатор (создает матрицу заданного размера заполненную 0)
	Matrix(const Matrix& copy); // Конструктор копирования 

	// Методы класса --------------------------------
	// Получение количества строк
	int getN() const
	{
		return n;
	}

	// Получение колисчества столбцов
	int getM() const
	{
		return m;
	}

	// Поиск максимума в матрице
	static double Max(double** arr_, const int& n_, const int& m_);

	// Получение матрицы в виде массива
	const double** asArray() const
	{
		return const_cast<const double**>(arr);
	}

	// Получение копии матрицы в виде массива
	double** getCopy();

	// Получение подматрицы
	double** getPodmatrix(const int& poz_n_, const int& poz_m_, const int& n_, const int& m_);

	// Перегрузки операторов ------------------------
	Matrix& operator= (const Matrix& copy); // Оператор присваивания
	Matrix operator+ (const Matrix& mat) const; // Оператор суммы
	Matrix operator* (const Matrix& mat) const; // Оператор произведения
	Matrix operator* (const int k) const; // Оператор произведения на число
	friend Matrix operator* (const int k, const Matrix& mat); // Оператор произведения на число
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat); // Оператор вывод матрицы в поток
	friend std::istream& operator>>(std::istream& out, Matrix& mat); // Оператор чтение матрицы из потока
	double* operator[] (int index); // Оператор индексации
	const double* operator[] (int index) const; // Оператор индексации константы
	bool operator==(const Matrix& mat) const; // Оператор сравнения матриц


	// Деструктор -----------------------------------
	~Matrix();

	// Класс исключений ----------------------------
	class MatrixExeption : public std::runtime_error
	{
	public:
		MatrixExeption(std::string s) : std::runtime_error(s) {}
		~MatrixExeption() {}
	};
protected:

	// Поля класса ----------------------------------
	int n, // Количество строк в матрице
		m; // Количество столбцов с матрице
	double** arr; // Матрица

	// Скрытые матоды класса ------------------------
	void initMat(); // Выделение памяти для матрицы
	void isInRange(int index) const; // Проверяет, находится ли индекс в допустимых границах
};
