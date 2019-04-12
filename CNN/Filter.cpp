#include "Filter.h"



Filter::Filter() : Matrix()
{
}

Filter::Filter(const int & i_, const int & j_ ) : Matrix(i_, j_)
{
}

Filter::Filter( int ** arr_, const int & i_, const int & j_) : Matrix(arr_, i_, j_)
{
}

Filter::Filter(const Filter & copy) : Matrix(copy)
{
}


Filter::~Filter()
{
}
