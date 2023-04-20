#ifndef __LAZYCPP_HPP__
#define __LAZYCPP_HPP__

#include "LazyValue.hpp"
#include "LazyInput.hpp"
#include "LazyConstant.hpp"
#include "LazyAddition.hpp"
#include "LazyMultiplication.hpp"
#include "LazySoustraction.hpp"

#include "LazyMultiplicationX.hpp"
#include "LazyAdditionX.hpp"


#include "LazyOpposite.hpp"
#include "LazyCosinus.hpp"
#include "LazySinus.hpp"

#include "LazyVariable.hpp"
#include "LazyManager.hpp"

void LazyAddOutput(LazyVariable& in,uint index,uint rank);

void LazyGetInfo();

uint LazyGetNbInputs();

uint LazyGetNbOutputs();

bool LazyIsZero(const LazyVariable& in);

bool LazyIsInput(const LazyVariable& in);

void LazyPrepare();

void LazyPrintGraph(LazyVariable& in);

void LazyPrintInputs();

void LazyPrintOutputGraph(uint index, uint cpt);

void LazyReInit();

void LazyReset();

double LazyUpdate(uint index, uint cpt);

void LazyUpdateAll();

#endif // __LAZYCPP_H__
