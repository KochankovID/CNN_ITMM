#include "NeyronCnn.h"



NeyronÑnn::NeyronÑnn() :  step(1)
{
}

NeyronÑnn::NeyronÑnn(const int& step_) : step(step_)
{
}

void NeyronÑnn::Padding(Matrix& a)
{
	Matrix copy(a.getN() + 2, a.getM() + 2);

	for (int i = 0; i < copy.getN(); i++) {
		for (int j = 0; j < copy.getM(); j++) {
			if ((i == 0)||(j == 0)||(j == (copy.getM() -1))||(i == (copy.getN() -1))) {
				copy[i][j] = 0;
			}
			else {
				copy[i][j] = a[i - 1][j - 1];
			}
		}
	}

	a = copy;
}

void NeyronÑnn::Pooling(Matrix& a,const int& n_, const int& m_)
{
	if ((n_ < 0) || (m_ < 0)||(n_ > a.getN())||(m_ > a.getM())) {
		throw NeyronÑnn::NeyronÑnnExeption("Íåâåğíûé ğàçìåğ ÿäğà!");
	}

	Matrix copy(a.getN() / n_, a.getM() / m_);

	for (int i = 0; i < copy.getN(); i++) {
		for (int j = 0; j < copy.getM(); j++) {
			copy[i][j] = Matrix::Max(a.getPodmatrix(i*n_, j*m_, n_, m_));
		}
	}
	a = copy;
}

void NeyronÑnn::Svertka(const Filter& F, Matrix& a)
{

	if ((step > a.getN()) || (step > a.getM())) {
		throw NeyronÑnnExeption("Çàäàí íåâîçìîæíûé øàã ñâåğòêè!");
	}

	Matrix rez((a.getN() - F.getN()) / step + 1, (a.getM() - F.getM()) / step + 1);

	double sum;
	Matrix fokus;
	for (int i = 0; i < rez.getN(); i++) {
		for (int j = 0; j < rez.getM(); j++) {
			sum = 0;
			fokus = a.getPodmatrix(i*step, j*step, F.getN(), F.getM());
			for (int ii = 0; ii < F.getN(); ii++) {
				for (int jj = 0; jj < F.getM(); jj++) {
					sum += fokus[ii][jj] * F[ii][jj];
				}
			}
			rez[i][j] = sum;
		}
	}
	a = rez;
}


NeyronÑnn::~NeyronÑnn()
{
}
