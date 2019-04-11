#pragma once
class Filter
{
public:
	// Конструкторы ----------------------------------------------------------
	Filter();
	Filter(const int& i_, const int& j_);
	Filter(const int** arr_, const int& i_, const int& j_);
	Filter(const Filter& copy);

	// Деструктор ------------------------------------------------------------
	~Filter();
};

