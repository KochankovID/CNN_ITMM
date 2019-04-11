#pragma once
#include <string>
class Matrix

{
public:
	// Конструкторы ---------------------------------
	Matrix(); // Конструктор по умолчанию -----------
	Matrix(int** arr, const int& i, const int& j); // Конструктор инициализатор
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

	// Получение матрицы в виде массива
	const int** asArray() const
	{
		return const_cast<const int**>(arr);
	}

	// Получение подматрицы
	int** getPodmatrix(const int& poz_n_, const int& poz_m_, const int& n_, const int& m_);

	// Перегрузки операторов ------------------------
	Matrix& operator= (const Matrix& copy); // Оператор присваивания
	Matrix operator+ (const Matrix& mat) const; // Оператор суммы
	Matrix operator* (const Matrix& mat) const; // Оператор произведения
	Matrix operator* (const int k) const; // Оператор произведения на число
	friend Matrix operator* (const int k, const Matrix& mat); // Оператор произведения на число
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat); // Оператор вывод матрицы в поток
	friend std::istream& operator>>(std::istream& out, Matrix& mat); // Оператор чтение матрицы из потока
	int* operator[] (int index); // Оператор индексации
	const int* operator[] (int index) const; // Оператор индексации константы
	bool operator==(const Matrix& mat) const; // Оператор сравнения матриц


	// Деструктор -----------------------------------
	~Matrix();

	// Класс исключений ----------------------------
	class MatrixExeption : std::runtime_error
	{
	public:
		MatrixExeption(std::string s) : std::runtime_error(s) {}
		~MatrixExeption() {}
	};
protected:

	// Поля класса ----------------------------------
	int n, // Количество строк в матрице
		m; // Количество столбцов с матрице
	int** arr; // Матрица

	// Скрытые матоды класса ------------------------
	void initMat(); // Выделение памяти для матрицы
	void isInRange(int index) const; // Проверяет, находится ли индекс в допустимых границах
};
