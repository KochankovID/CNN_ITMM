#include "NeyronCnn.h"



Neyron—nn::Neyron—nn() :  n(0), m(0)
{
}

Neyron—nn::Neyron—nn(const int & i_, const int & j_) : n(i_), m(j_)
{
	arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int [m];
	}
}

Neyron—nn::Neyron—nn(const int ** arr_, const int & i_, const int & j_) : n(i_), m(j_)
{
	arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = arr_[i][j];
		}
	}
}

Neyron—nn::Neyron—nn(const Neyron—nn & copy) : n(copy.n), m(copy.m)
{
	arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = copy[i][j];
		}
	}
}

void Neyron—nn::Padding()
{
	n += 2;
	m += 2;
	int** copy;
	copy = new int*[n];
	for (int i = 0; i < n; i++) {
		copy[i] = new int[m];
	}
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < m-1; j++) {
			copy[i][j] = arr[i][j];
		}
	}
	for (int i = 0; i < n - 2; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = copy;
}

void Neyron—nn::Svertka()
{
}

Neyron—nn::~Neyron—nn()
{
}
