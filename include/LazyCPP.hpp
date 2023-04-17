#ifndef __LAZYCPP_HPP__
#define __LAZYCPP_HPP__

#include "LazyValue.hpp"
#include "LazyInput.hpp"
#include "LazyConstant.hpp"
#include "LazyAddition.hpp"
#include "LazyMultiplication.hpp"
#include "LazySoustraction.hpp"

#include "LazyCosinus.hpp"
#include "LazySinus.hpp"

#include "LazyVariable.hpp"
#include "LazyManager.hpp"

void LazyAddOutput(LazyVariable& in);

void LazyGetInfo();

uint LazyGetNbInputs();

bool LazyIsZero(const LazyVariable& in);

void LazyPrepare();

void LazyPrintGraph(LazyVariable& in);

void LazyReInit();

double LazyUpdate(uint index);

void LazyUpdateAll();

#endif // __LAZYCPP_H__
