#pragma once
#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
extern "C" { __declspec(dllexport) void Set(int i, int j); }
extern "C" { __declspec(dllexport) int Neyroset(double ooo[]); }
extern "C" { __declspec(dllexport) void startNeyroset(); }