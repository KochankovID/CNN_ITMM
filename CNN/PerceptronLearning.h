#pragma once
#include "Weights.h"
#include "NeyronPerceptron.h"
#include <cstdlib>

template<typename T, typename Y>
class PerceptronLearning
{
public:
	// ������������ ----------------------------------------------------------
	PerceptronLearning(); // �� ���������
	PerceptronLearning(const double& E_); // �������������
	PerceptronLearning(const NeyronPerceptron<T,Y>& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	// �������� ������������ ����������� ������� ��������� ��������������� ������
	void WTSimplePerceptron(const Y& a, const Y& y, Weights<T>& w, const Matrix<T>& in);
	
	// ����� ��������� ��������������� ������
	static void BackPropagation(Matrix<Weights<T>>& w, const Weights<T>& y);
	static void BackPropagation(Matrix<Weights<T>>& w, const Matrix<Weights<T>>& y);

	// ����� ������������ ������
	void GradDes(Weights<T>& w, Matrix<T>& in, Func<T, Y>& F, const T& x);

	// ����� ���������� ������� ������������ ������
	static Y RMS_error(const Y* a, const Y* y, const int& lenth);

	// ����� ���������� ������ ��������� ����
	static Y PartDOutLay(const Y& a, const Y& y);

	// ����� ���������� �����
	void retract(Matrix<Weights<T>>& weights,const int& decs);
	void retract(Weights<T>& weights, const int& decs);

	// ��������� ������������������
	void shuffle(int* arr, const int& lenth);

	// ����� ��������� ������� � ��������� ��������
	double& getE() { return E; };

	// ���������� ���������� -------------------------------------------------
	PerceptronLearning& operator= (const PerceptronLearning& copy) = delete; // ������ �����������
	friend std::ostream& operator<<(std::ostream& out, const PerceptronLearning& mat) = delete; // ������ ������ � �����
	friend std::istream& operator>>(std::istream& out, PerceptronLearning& mat) = delete; // ������ ���������� �� ������

	// ���������� ------------------------------------------------------------
	~PerceptronLearning();

	// ����� ���������� ------------------------------------------------------
	class LearningExeption : public std::runtime_error {
	public:
		LearningExeption(std::string str) : std::runtime_error(str) {};
		~LearningExeption() {};
	};
protected:
	// ���� ������ ----------------------------------
	double E; // �������� ��������
};

template<typename T, typename Y>
inline PerceptronLearning<T,Y>::PerceptronLearning() : E(1)
{
}

template<typename T, typename Y>
inline PerceptronLearning<T, Y>::PerceptronLearning(const double & E_) : E(E_)
{
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::WTSimplePerceptron(const Y & a, const Y & y, Weights<T> & w, const Matrix<T>& in)
{
	if ((w.getN() != in.getN()) || (w.getM() != in.getM())) {
		throw LearningExeption("������������ �������� ������� ������� � ������� �����!");
	}
	T delta = a - y;
	T ii = 0;
	if (delta == 0) {
		return;
	}
	for (int i = 0; i < w.getN(); i++) {
		for (int j = 0; j < w.getM(); j++) {
			ii = w[i][j] + E * delta*in[i][j];
			w[i][j] = ii;
		}
	}
	w.GetWBias() += E * delta;
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::BackPropagation(Matrix<Weights<T>>& w, const Weights<T>& y)
{
	for (int i = 0; i < y.getN(); i++) {
		for (int j = 0; j < y.getM(); j++) {
			w[i][j].GetD() += (y[i][j] * y.GetD());
		}
	}
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::BackPropagation(Matrix<Weights<T>>& w, const Matrix<Weights<T>>& y)
{
	for (int o = 0; o < y.getN(); o++) {
		for (int u = 0; u < y.getM(); u++) {
			for (int i = 0; i < y[o][u].getN(); i++) {
				for (int j = 0; j < y[o][u].getM(); j++) {
					w[i][j].GetD() += (y[o][u][i][j] * y.GetD());
				}
			}
		}
	}
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::GradDes(Weights<T>& w, Matrix<T>& in, Func<T, Y>& F, const T& x)
{
	if ((w.getN() != in.getN()) || (w.getM() != in.getM())) {
		throw LearningExeption("������������ �������� ������� ������� � ������� �����!");
	}

	for (int i = 0; i < w.getN(); i++) {
		for (int j = 0; j < w.getM(); j++) {
			w[i][j] += (w.GetD() * E * F(x) * in[i][j]);
		}
	}
	w.GetWBias() += E * F(x) * w.GetD();
}


template<typename T, typename Y>
inline Y PerceptronLearning<T, Y>::RMS_error(const Y * a, const Y * y, const int & lenth)
{
	Y err = 0;
	for (int i = 0; i < lenth; i++) {
		err += (a[i] - y[i])*(a[i] - y[i]);
	}
	err /= 2;
	return err;
}

template<typename T, typename Y>
inline Y PerceptronLearning<T, Y>::PartDOutLay(const Y & a, const Y & y)
{
	return 2*(a - y);
}

template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::retract(Matrix<Weights<T>>& weights, const int & decs)
{
	int d = 1;
	for (int i = 0; i < decs; i++) {
		d *= 0.1;
	}
	for (int i = 0; i < weights.getN(); i++) {
		for (int j = 0; j < weights.getM(); j++) {
			for (int k = 0; k < weights[i][j].getN(); k++) {
				for (int y = 0; y < weights[i][j].getM(); y++) {
					if (weights[i][j][k][y] > 0) {
						weights[i][j][k][y] -= d;
					}
					else {
						weights[i][j][k][y] += d;
					}
				}
			}
		}
	}
}



template<typename T, typename Y>
inline void PerceptronLearning<T, Y>::shuffle(int * arr, const int & lenth)
{
	srand(time(0));
	int j = 0;
	int tmp = 0;
	for (int i = 0; i < lenth; i++) {
		j = ((double)rand()/INT_MAX*lenth);
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
}

template<typename T, typename Y>
inline PerceptronLearning<T, Y>::~PerceptronLearning()
{
}
