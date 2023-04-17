#ifndef __LAZYCPP_HPP__
#define __LAZYCPP_HPP__



#include "LazyValue.hpp"
#include "LazyInput.hpp"
#include "LazyConstant.hpp"
#include "LazyAddition.hpp"
#include "LazySoustraction.hpp"
#include "LazyMultiplication.hpp"

#include "LazyVariable.hpp"
#include "LazyManager.hpp"

void GetLazyInfo();

void AddLazyOutput(LazyVariable& in);

void PrintGraph(LazyVariable& in);

void LazyPrepare();

void LazyUpdate(uint index);

void LazyUpdateAll();

#endif // __LAZYCPP_H__
