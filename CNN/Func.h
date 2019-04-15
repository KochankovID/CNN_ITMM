#pragma once

template<typename Y>
class Func {
public:
	Func() {};
	virtual Y operator()() = 0;
};