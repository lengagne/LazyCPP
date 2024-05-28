#ifndef __LAZYCPP_HPP__
#define __LAZYCPP_HPP__

#include "LazyValue.hpp"
#include "LazyInput.hpp"
#include "LazyConstant.hpp"
#include "LazyAddition.hpp"
#include "LazyMultiplication.hpp"
#include "LazyMultiplicationX.hpp"
#include "LazyAdditionX.hpp"
#include "LazySoustraction.hpp"
#include "LazyCosinus.hpp"
#include "LazySinus.hpp"
#include "LazyVariable.hpp"

class LazyVariable;

void LazyAddOutput(const LazyVariable& in,uint index,uint rank);

void LazyCleanFiles();

uint LazyGetNbInputs();

void LazyPrepare(const std::string& filename="",
                 bool reuse_if_exist = false);

void LazyPrintAll();

void LazyPrintAllInputs();

void LazyPrintAllOutputs();

void LazyReset();

void LazyUpdateInput();

void LazyUpdateInput(uint index, double value);

double LazyUpdateOutput(uint index, uint cpt);

#endif // __LAZYCPP_H__
