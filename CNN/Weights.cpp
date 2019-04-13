#include "Weights.h"



Weights::Weights() : Matrix()
{
}

Weights::Weights(const int & i_, const int & j_) : Matrix(i_, j_)
{
}

Weights::Weights(double ** arr_, const int & i_, const int & j_) : Matrix(arr_, i_, j_)
{
}

Weights::Weights(const Weights & copy) : Matrix(copy)
{
}


Weights::~Weights()
{
}
